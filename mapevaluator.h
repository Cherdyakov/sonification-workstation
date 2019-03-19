#ifndef MAPEVALUATOR_H
#define MAPEVALUATOR_H

#include <algorithm>
#include "external/exprtk/exprtk.hpp"

namespace sow {

template<class T>
class MapEvaluator
{
public:

    MapEvaluator();
    ~MapEvaluator();
    std::vector<std::string> extractVariables(std::string expression);

private:

    bool isCapital(char c);
    void unique(std::vector<std::string> &vec);

};

template<class T>
MapEvaluator<T>::MapEvaluator() { }
template<class T>
MapEvaluator<T>::~MapEvaluator() {}

template<class T>
std::vector<std::string> MapEvaluator<T>::extractVariables(std::string expression) {
    expression = expression + " ";
    std::vector<std::string> variables = {};
    std::string substring;
    size_t consecutiveCharsCaps = 0;
    bool previousCharCaps = false;
    for (size_t i = 0; i < expression.length(); i++)
    {
        if (isCapital(expression[i]))
        {
            consecutiveCharsCaps++;
            previousCharCaps = true;
        }
        else {
            if(previousCharCaps) {
                substring = expression.substr(i - consecutiveCharsCaps, consecutiveCharsCaps);
                variables.push_back(substring);
                consecutiveCharsCaps = 0;
                previousCharCaps = false;
            }
        }
    }
    unique(variables);
    return variables;
}

template <class T>
void MapEvaluator<T>::unique(std::vector<std::string> &vec)
{
    auto end = vec.end();
    for (auto it = vec.begin(); it != end; ++it) {
        end = std::remove(it + 1, end, *it);
    }
    vec.erase(end, vec.end());
}

template<class T>
bool MapEvaluator<T>::isCapital(char c) {
    return (c >='A' && c <= 'Z');
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
