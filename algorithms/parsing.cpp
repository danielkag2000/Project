#include "parsing.h"
#include <stack>
#include "../exceptions.h"
#include "../exp/exp.h"
#include "../exp/expression_types.h"
#include <regex>

Expression* complicate_expression(const vector<string>& parameters, SymbolTable& var_table, const string& op);
Expression* base_expression(SymbolTable& var_table, const string& op);

Expression* parsing(operators op_table, SymbolTable var_table, vector<string> tokens) {
    //the parameters to the function
    vector<string> parameters;
    // the "numbers are the non operators
    stack<string> numbers;
    int number_of_tokens = tokens.size();
    string token;

    for(int i = 0; i < number_of_tokens - 1; i++) {
        token = tokens[i];
        // if it is not an operator
        if (op_table.find(token) == op_table.end()) {
            numbers.push(token);

        } else { // it is an operator
            int parm_num = op_table[token];
            for (int j = 0; j < parm_num; j++) {
                if (numbers.empty()) {
                    throw SyntaxException("too few parameters");
                }
                parameters.push_back(numbers.top());
                numbers.pop();
            }
            Expression* exp = parser(parameters, var_table, token);
            numbers.push(to_string(exp->calculate(var_table.asMap())));
            parameters.clear();
            delete exp;
        }
    }

    // get the last command

    int parm_num = op_table[token];
    token = tokens[parm_num - 1];

    if (op_table.find(token) == op_table.end()) {
        throw SyntaxException("too many parameters");
    }

    // too many parameters
    if (!numbers.empty()) {
        throw SyntaxException("too few parameters");
    }

    return parser(parameters, var_table, token);
}

Expression* parser(vector<string> parameters, SymbolTable var_table, string func_operator) {
    if (func_operator == "+" || func_operator == "-" || func_operator == "*" || func_operator == "/"
        || func_operator == "==" || func_operator == "!=" || func_operator == "<" || func_operator == ">"
        || func_operator == "<=" || func_operator == ">=") {
        return complicate_expression(parameters, var_table, func_operator);
    }

    return nullptr;
}

bool isNumber(const string& s) {
    regex r;
    try {
        r = regex("-?\\d+(\\.\\d+)?");
    } catch (...) {
        throw Exception("couldn't create the regex");
    }
    return regex_match(s, r);
}

Expression* complicate_expression(const vector<string>& parameters, SymbolTable& var_table, const string& op) {

    if (op == "+")
        return new Plus(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));

    if (op == "-")
        return new Minus(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));

    if (op == "*")
        return new Mul(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));

    if (op == "/")
        return new Div(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));

    if (op == "==")
        return new Equal(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));

    if (op == "!=")
        return new NotEqual(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));

    if (op == "<")
        return new Less(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));

    if (op == ">")
        return new Greater(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));

    if (op == "<=")
        return new LessEqual(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));

    if (op == ">=")
        return new GreaterEqual(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));

    // not found
    return nullptr;
}

Expression* base_expression(SymbolTable& var_table, const string& op) {
        if (var_table.exists(op)) {
            return new Var(op);

        } else if (isNumber(op)) {
            return new Num(op);
        }

        throw SyntaxException("bad expression");
}