#ifndef MAPEVALUATOR_H
#define MAPEVALUATOR_H

#include <algorithm>
#include <QDebug>
#include <tuple>
#include "external/exprtk/exprtk.hpp"
#include "utility.h"

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
    bool compileExpression(const std::string expressionStr, const std::vector<T> * const data);
    bool testCompileExpression(const std::string expressionStr, const std::vector<T> * const data);
    T value(const std::vector<T> * const data);

private:

    exprtkSymbolTable* symbolTable_ = nullptr;
    exprtkExpression* expression_ = nullptr;
    exprtkParser parser_;
    std::vector<MapVariable<T>> currentVariables_;

    std::vector<std::string> extractVariables(std::string expression);
    std::vector<MapVariable<T>> createVariables(const std::string expression);

};

template<class T>
MapEvaluator<T>::MapEvaluator() { }
template<class T>
MapEvaluator<T>::~MapEvaluator() {}

template<class T>
T MapEvaluator<T>::value(const std::vector<T> * const data) {
    // Update variable values.
    for(MapVariable<T>& var : currentVariables_) {
        var.value = data->at(var.idx);
    }
    // Re-evaluate current expression.
    float val = expression_->value();
    return val;
}

template<class T>
bool MapEvaluator<T>::compileExpression(const std::string expressionStr, const std::vector<T> * const data) {

    if(expression_ != nullptr) {
        delete expression_;
    }
    if(symbolTable_ != nullptr) {
        delete symbolTable_;
    }

    expression_ = new exprtkExpression;
    symbolTable_ = new exprtkSymbolTable;

    currentVariables_ = createVariables(expressionStr);

    // Can't have more variables than there are data columns.
    if(currentVariables_.size() > data->size()) return false;

    // Get index values for the variables names;
    for (MapVariable<T>& var : currentVariables_) {
        var.idx = utility::alphaToInt(var.alpha);
    }

    // Check that all indexes are valid.
    for (MapVariable<T>& var : currentVariables_) {
        if (var.idx > data->size() - 1) return false;
    }

    // Get data values with the indexes.
    for (MapVariable<T>& var : currentVariables_) {
        var.value = data->at(var.idx);
    }

    // Add variables to the exprtk symbol table.
    for (MapVariable<T>& var : currentVariables_) {
        symbolTable_->add_variable(var.alpha, var.value);
    }

    symbolTable_->add_constants();
    expression_->register_symbol_table(*symbolTable_);
    // Attempt compilation and return success.
    bool success = parser_.compile(expressionStr, *expression_);
    float val = expression_->value();
    return success;
}

template<class T>
bool MapEvaluator<T>::testCompileExpression(const std::string expressionStr, const std::vector<T> * const data) {

    exprtkSymbolTable testTable;
    exprtkExpression testExpression;
    exprtkParser testParser;
    std::vector<MapVariable<T>> testVariables;

    testVariables = createVariables(expressionStr);

    // Can't have more variables than there are data columns.
    if(testVariables.size() > data->size()) return false;

    // Get index values for the variables names;
    for (MapVariable<T>& var : testVariables) {
        var.idx = utility::alphaToInt(var.alpha);
    }

    // Check that all indexes are valid.
    for (MapVariable<T>& var : testVariables) {
        if (var.idx > data->size() - 1) return false;
    }

    // Get data values with the indexes.
    for (MapVariable<T>& var : testVariables) {
        var.value = data->at(var.idx);
    }

    // Add variables to the exprtk symbol table.
    for (MapVariable<T>& var : testVariables) {
        testTable.add_variable(var.alpha, var.value);
    }

    testTable.add_constants();
    testExpression.register_symbol_table(testTable);
    // Attempt compilation and return success.
    bool success = testParser.compile(expressionStr, testExpression);
    float val = testExpression.value();
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
