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
