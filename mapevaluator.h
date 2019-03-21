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
public:

    MapEvaluator();
    ~MapEvaluator();
    bool compileExpression(const std::string expressionStr, const std::vector<T> * const data);

private:

    std::vector<std::string> extractVariables(std::string expression);
    std::vector<MapVariable<T>> createVariables(const std::string expression);

};

template<class T>
MapEvaluator<T>::MapEvaluator() { }
template<class T>
MapEvaluator<T>::~MapEvaluator() {}

template<class T>
bool MapEvaluator<T>::compileExpression(const std::string expressionStr, const std::vector<T> * const data) {

    std::vector<MapVariable<T>> variables = createVariables(expressionStr);

    // Can't have more variables than there are data columns.
    if(variables.size() > data->size()) return false;

    // Get index values for the variables names;
    for (MapVariable<T>& var : variables) {
        var.idx = utility::alphaToInt(var.alpha);
    }

    // Check that all indexes are valid.
    for (MapVariable<T>& var : variables) {
        if (var.idx > data->size() - 1) return false;
    }

    // Get data values with the indexes.
    for (MapVariable<T>& var : variables) {
        var.value = data->at(var.idx);
    }

    typedef exprtk::symbol_table<T> symbol_table_t;
    typedef exprtk::expression<T>     expression_t;
    typedef exprtk::parser<T>             parser_t;

    symbol_table_t symbol_table;

    for (MapVariable<T>& var : variables) {
        symbol_table.add_variable(var.alpha, var.value);
    }

    symbol_table.add_constants();

    expression_t expression;
    expression.register_symbol_table(symbol_table);

    parser_t parser;

    bool success = parser.compile(expressionStr, expression);

    T y = expression.value();


    // If (success) pass map to Parameter backing class.

    qDebug() << "Variables: ";
    for(MapVariable<T>& var : variables) {
        qDebug() << QString::fromStdString(var.alpha) << " " << var.idx << " " << var.value;
    }

    qDebug() << "Value: " << y;

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
