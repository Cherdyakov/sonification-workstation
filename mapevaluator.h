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
    bool compileExpression(const std::string expression, const std::vector<T> * const data);

private:

    std::vector<std::string> extractVariables(std::string expression);
    std::vector<MapVariable<T>> createVariables(const std::string expression);

};

template<class T>
MapEvaluator<T>::MapEvaluator() { }
template<class T>
MapEvaluator<T>::~MapEvaluator() {}

template<class T>
bool MapEvaluator<T>::compileExpression(const std::string expression, const std::vector<T> * const data) {

    //    std::vector<std::string> variables = extractVariables(expression);

    std::vector<MapVariable<T>> variables = createVariables(expression);

    // Get index values for the variables names;
    for (MapVariable<T>& var : variables) {
        var.idx = utility::alphaToInt(var.alpha);
    }

    // Get data values with the indexes.
    for (MapVariable<T>& var : variables) {
        var.value = data->at(var.idx);
    }



    //    for(size_t& idx : indexes) {

    //    }

    // Create expression.

    // Register symbol table.

    // Create parser.

    // Attempt expression compilation.

    // If (success) pass map to Parameter backing class.

    qDebug() << "Variables: ";
    for(MapVariable<T>& var : variables) {
        qDebug() << QString::fromStdString(var.alpha) << " " << var.idx << " " << var.value;
    }


    // Return success.
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


template<class T>
std::vector<std::string> MapEvaluator<T>::extractVariables(std::string expression) {

    std::set<std::string> vars;

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
            vars.insert(std::string(first, var_end));
        }

        first = var_end;
    }

    return std::vector<std::string>(vars.cbegin(), vars.cend());
}

//    void evaluate()
//    {
//        typedef exprtk::symbol_table<T> symbol_table_t;
//        typedef exprtk::expression<T>     expression_t;
//        typedef exprtk::parser<T>             parser_t;

//        std::string expression_string = "clamp(-1.0,sin(2 * pi * x) + cos(x / 2 * pi),+1.0)";

//        T x;

//        symbol_table_t symbol_table;
//        symbol_table.add_variable("x",x);
//        symbol_table.add_constants();

//        expression_t expression;
//        expression.register_symbol_table(symbol_table);

//        parser_t parser;
//        parser.compile(expression_string,expression);

//        for (x = T(-5); x <= T(+5); x += T(0.001))
//        {
//            T y = expression.value();
//            printf("%19.15f\t%19.15f\n",x,y);
//        }
//    }

} // namespace sow

#endif // MAPPER_H
