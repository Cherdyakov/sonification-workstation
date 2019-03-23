#ifndef MAPEVALUATOR_H
#define MAPEVALUATOR_H

#include <algorithm>
#include <QDebug>
#include <tuple>
#include "external/exprtk/exprtk.hpp"
#include "utility.h"
#include "dataset.h"
#include "commands.h"

namespace sow {

template<class T>
struct MapVariable {
    std::string alpha;
    size_t idx;
    T value;
};

template<class T>
class MapEvaluator
{

    // exprtk types.
    typedef exprtk::symbol_table<T>   exprtkSymbolTable;
    typedef exprtk::expression<T>     exprtkExpression;
    typedef exprtk::parser<T>             exprtkParser;

public:

    MapEvaluator();
    ~MapEvaluator();
    void setData(const Dataset *dataset, const std::vector<T> *currentData);
    bool compileExpression(const std::string expressionStr);
    bool testCompileExpression(const std::string expressionStr);
    T value();
    T scaledValue(T outLow, T outHigh);

private:

    // Dataset and related values.
    const std::vector<T>* currentData_ = nullptr;
    const Dataset* dataset_ = nullptr;
    T expressionMin_;
    T expressionMax_;
    // exprtk variables.
    exprtkSymbolTable* symbolTable_ = nullptr;
    exprtkSymbolTable* minMaxTable_ = nullptr;
    exprtkExpression* expression_ = nullptr;
    exprtkParser parser_;
    std::vector<MapVariable<T>> currentVariables_;
    std::string currentExpressionString_;

    std::vector<std::string> extractVariables(std::string expression);
    std::vector<MapVariable<T>> createVariables(const std::string expression);
    T calculateValue();
    void calculateMinMax();
    T scale(T x, T inLow, T inHigh, T outLow, T outHigh, T exp);

};

template<class T>
MapEvaluator<T>::MapEvaluator() { }
template<class T>
MapEvaluator<T>::~MapEvaluator() {}

template<class T>
void MapEvaluator<T>::setData(const Dataset* dataset, const std::vector<T>* currentData)
{
    dataset_ = dataset;
    currentData_ = currentData;
}

template<class T>
T MapEvaluator<T>::value() {
    // Update variable values.
    for(MapVariable<T>& var : currentVariables_) {
        var.value = currentData_->at(var.idx);
    }
    // Re-evaluate current expression.
    float val = expression_->value();
    return val;
}

template<class T>
T MapEvaluator<T>::scale(T x, T inLow, T inHigh, T outLow, T outHigh, T exp)
{
    return ((x-inLow)/(inHigh-inLow) == 0.0) ? outLow :
                                               (((x-inLow)/(inHigh-inLow)) > 0.0) ?
                                                   (outLow + (outHigh-outLow) * pow(((x-inLow)/(inHigh-inLow)),exp)) :
                                                   (outLow + (outHigh-outLow) * -(pow((((-x+inLow)/(inHigh-inLow))),exp)));
}

template<class T>
T MapEvaluator<T>::scaledValue(T outLow, T outHigh)
{
    //    return scale(value(), );
}

template<class T>
void MapEvaluator<T>::calculateMinMax()
{
    // If there is no data, expression is constant
    // and min = max = expression value.
    if(!dataset_->hasData()) {
        expressionMin_ = expressionMax_ = value();
        return;
    }

    exprtkExpression minMaxExpression;
    exprtkSymbolTable minMaxSymbolTable;
    exprtkParser minMaxParser;
    std::vector<MapVariable<T>> minMaxVariables;
    std::vector<T> minMaxCurrentData = dataset_->getRow(0);

    minMaxVariables = createVariables(currentExpressionString_);

    // Get index values for the variables names;
    for (MapVariable<T>& var : minMaxVariables) {
        var.idx = utility::alphaToInt(var.alpha);
        var.value = minMaxCurrentData.at(var.idx);
        minMaxSymbolTable.add_variable(var.alpha, var.value);
    }
    minMaxSymbolTable.add_constants();
    minMaxExpression.register_symbol_table(minMaxSymbolTable);
    // Attempt compilation and return success.
    bool success = minMaxParser.compile(currentExpressionString_, minMaxExpression);

    expressionMin_ = expressionMax_ = minMaxExpression.value();

    for(size_t i = 1; i < dataset_->rows(); i++) {
        minMaxCurrentData = dataset_->getRow(i);
        // Update variable values.
        for(MapVariable<T>& var : minMaxVariables) {
            var.value = minMaxCurrentData.at(var.idx);
        }
        // Re-evaluate current expression.
        float val = minMaxExpression.value();
        if(val < expressionMin_) {
            expressionMin_ = val;
        } else if (val > expressionMax_) {
            expressionMax_ = val;
        }
    }

    qDebug() << "Min: " << expressionMin_ << "Max: " << expressionMax_;
}

template<class T>
bool MapEvaluator<T>::compileExpression(const std::string expressionStr) {

    currentExpressionString_ = expressionStr;

    if(expression_ != nullptr) {
        delete expression_;
    }
    if(symbolTable_ != nullptr) {
        delete symbolTable_;
    }

    expression_ = new exprtkExpression;
    symbolTable_ = new exprtkSymbolTable;

    currentVariables_ = createVariables(currentExpressionString_);

    // Can't have more variables than there are data columns.
    if(currentVariables_.size() > (currentData_ ? currentData_->size() : 0)) return false;

    // Get index values for the variables names;
    for (MapVariable<T>& var : currentVariables_) {
        var.idx = utility::alphaToInt(var.alpha);
    }

    // Check that all indexes are valid.
    for (MapVariable<T>& var : currentVariables_) {
        if (var.idx > currentData_->size() - 1) return false;
    }

    // Get data values from indexes and add vars to table.
    for (MapVariable<T>& var : currentVariables_) {
        var.value = currentData_->at(var.idx);
        symbolTable_->add_variable(var.alpha, var.value);
    }

    symbolTable_->add_constants();
    expression_->register_symbol_table(*symbolTable_);
    // Attempt compilation and return success.
    bool success = parser_.compile(currentExpressionString_, *expression_);

    if(success) {
        calculateMinMax();
    }

    return success;
}

template<class T>
bool MapEvaluator<T>::testCompileExpression(const std::string expressionStr) {

    exprtkSymbolTable testTable;
    exprtkExpression testExpression;
    exprtkParser testParser;
    std::vector<MapVariable<T>> testVariables;

    testVariables = createVariables(expressionStr);

    // Can't have more variables than there are data columns.
    if(testVariables.size() > (currentData_ ? currentData_->size() : 0)) return false;

    // Get index values for the variables names;
    for (MapVariable<T>& var : testVariables) {
        var.idx = utility::alphaToInt(var.alpha);
    }

    // Check that all indexes are valid.
    for (MapVariable<T>& var : testVariables) {
        if (var.idx > currentData_->size() - 1) return false;
    }

    // Get data values from indexes and add vars to table.
    for (MapVariable<T>& var : testVariables) {
        var.value = currentData_->at(var.idx);
        testTable.add_variable(var.alpha, var.value);
    }

    testTable.add_constants();
    testExpression.register_symbol_table(testTable);
    // Attempt compilation and return success.
    bool success = testParser.compile(expressionStr, testExpression);

    return success;
}

template<class T>
std::vector<MapVariable<T>> MapEvaluator<T>::createVariables(const std::string expression) {
    std::vector<MapVariable<T>> variables;

    for (auto first = expression.cbegin(); first != expression.cend(); )
    {
        auto var_end = std::adjacent_find(first, expression.cend(),
                                          [](char a, char b) { return std::isupper(a) != std::isupper(b); });

        if (var_end != expression.cend())
        {
            ++var_end;
        }

        if (std::isupper(*first))
        {
            MapVariable<T> variable = { std::string(first, var_end), 0, 0.0f };
            variables.push_back(variable);
        }

        first = var_end;
    }

    return variables;
}

} // namespace sow

#endif // MAPPER_H
