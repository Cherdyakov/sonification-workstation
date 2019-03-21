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

private:

    exprtkSymbolTable symbolTable_;
    exprtkExpression expression_;
    exprtkParser parser_;

    std::vector<MapVariable<T>> currentVariables;

    std::vector<std::string> extractVariables(std::string expression);
    std::vector<MapVariable<T>> createVariables(const std::string expression);

};

template<class T>
MapEvaluator<T>::MapEvaluator() { }
template<class T>
MapEvaluator<T>::~MapEvaluator() {}

template<class T>
bool MapEvaluator<T>::compileExpression(const std::string expressionStr, const std::vector<T> * const data) {

    currentVariables = createVariables(expressionStr);

    // Can't have more variables than there are data columns.
    if(currentVariables.size() > data->size()) return false;

    // Get index values for the variables names;
    for (MapVariable<T>& var : currentVariables) {
        var.idx = utility::alphaToInt(var.alpha);
    }

    // Check that all indexes are valid.
    for (MapVariable<T>& var : currentVariables) {
        if (var.idx > data->size() - 1) return false;
    }

    // Get data values with the indexes.
    for (MapVariable<T>& var : currentVariables) {
        var.value = data->at(var.idx);
    }

    for (MapVariable<T>& var : currentVariables) {
        symbolTable_.add_variable(var.alpha, var.value);
    }

    symbolTable_.add_constants();

    expression_.register_symbol_table(symbolTable_);

    bool success = parser_.compile(expressionStr, expression_);

    if (success) {
        qDebug() << expression_.value();
    }

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
