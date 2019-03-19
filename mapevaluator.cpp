//#include "mapevaluator.h"
//namespace sow {

//template<class T>
//void evaluate()
//{
//    typedef exprtk::symbol_table<T> symbol_table_t;
//    typedef exprtk::expression<T>     expression_t;
//    typedef exprtk::parser<T>             parser_t;

//    std::string expression_string = "clamp(-1.0,sin(2 * pi * x) + cos(x / 2 * pi),+1.0)";

//    T x;

//    symbol_table_t symbol_table;
//    symbol_table.add_variable("x",x);
//    symbol_table.add_constants();

//    expression_t expression;
//    expression.register_symbol_table(symbol_table);

//    parser_t parser;
//    parser.compile(expression_string,expression);

//    for (x = T(-5); x <= T(+5); x += T(0.001))
//    {
//        T y = expression.value();
//        printf("%19.15f\t%19.15f\n",x,y);
//    }
//}

//bool MapEvaluator::isCapital(char x)
//{
//    return (x >='A' && x <= 'Z');
//}

//std::vector<char> MapEvaluator::extractVariables(std::string expression) {
//    std::vector<char> variables = {};
//    for (size_t i = 0;i < expression.length() ;i++)
//    {
//        if (isCapital(expression[i]))
//        {
//            variables.push_back(expression[i]);
//        }
//    }
//    return variables;
//}

//}

