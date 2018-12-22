#include "parsing.h"
#include <stack>
#include "../exceptions.h"
#include "../exp/exp.h"
#include "../exp/expression_types.h"
#include "../command/command.h"
#include "../command/simple_commands.h"
#include "lexer.h"
#include "shunting_yard_algorithm.h"
#include "../command/complicate_commands.h"
#include <regex>
#include "../command/server_command.h"
#include <algorithm>

Expression* complicate_expression(const vector<string>& parameters, SymbolTable& var_table, const string& op);
Expression* base_expression(SymbolTable& var_table, const string& op);

Expression* parsing(operators op_table, SymbolTable& var_table, vector<string> tokens) {

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

            int parm_num = op_table.find(token)->second;
            for (int j = 0; j < parm_num; j++) {
                if (numbers.empty()) {
                    throw SyntaxException("too few parameters");
                }
                parameters.push_back(numbers.top());
                numbers.pop();
            }
            reverse(parameters.begin(), parameters.end()); // because the order is reversed

            Expression* exp = parser(parameters, var_table, token);
            double res = exp->calculate(var_table);
            if (res != NAN) {
                if (exp->returnValue(var_table) != "") {
                    numbers.push(exp->returnValue(var_table));
                }
            }
            parameters.clear();
            delete exp;
        }
    }

    // get the last command
    token = tokens[number_of_tokens - 1];

    if (op_table.find(token) == op_table.end()) {
        throw SyntaxException("too many parameters");
    }

    int param_num = op_table.find(token)->second;
    for (int i = 0; i < param_num; i++) {
        if (numbers.empty()) {
            throw SyntaxException("too few parameters");
        }
        parameters.push_back(numbers.top());
        numbers.pop();
    }
    reverse(parameters.begin(), parameters.end()); // because the order is reversed

    // too many parameters
    if (!numbers.empty()) {
        throw SyntaxException("too many parameters");
    }

    return parser(parameters, var_table, token);
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

Expression* parser(vector<string> parameters, SymbolTable& var_table, string func_operator) {
    if (func_operator == "+" || func_operator == "-" || func_operator == "*" || func_operator == "/"
        || func_operator == "==" || func_operator == "!=" || func_operator == "<" || func_operator == ">"
        || func_operator == "<=" || func_operator == ">=") {
        return complicate_expression(parameters, var_table, func_operator);
    }

    if (func_operator == "=") {
        Expression* exp = base_expression(var_table, parameters[1]);
        Expression* result = new CommandExpression(new AssignCommand(parameters[0], exp->calculate(var_table)));
        delete exp;
        return result;
    }

    if (func_operator == "var") {
        return new CommandExpression(new VarCommand(parameters[0]));
    }

    if (func_operator == "=bind" || func_operator == "bind") {
        return new CommandExpression(new BindCommand(parameters[0], parameters[1]));
    }

    if (func_operator == "print") {
        return new CommandExpression(new PrintCommand(parameters[0]));
    }

    if (func_operator == "sleep") {
        Expression* exp = base_expression(var_table, parameters[0]);
        Expression* result = new CommandExpression(new SleepCommand((int)exp->calculate(var_table)));
        delete exp;
        return result;
    }

    if (func_operator == "openDataServer") {
        Expression* exp1 = base_expression(var_table, parameters[0]);
        Expression* exp2 = base_expression(var_table, parameters[1]);
        Expression* result = new CommandExpression(new OpenDataServerCommand((int)exp2->calculate(var_table),
                                                                            (int)exp1->calculate(var_table)));
        delete exp1;
        delete exp2;
        return result;
    }

    if (func_operator == "connect") {
        Expression* exp = base_expression(var_table, parameters[1]);
        Expression* result = new CommandExpression(new ConnectCommand(parameters[0], (int)exp->calculate(var_table)));
        delete exp;
        return result;
    }

    return nullptr;
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



Expression* parser_complicate(string op, vector<string> lex_bool_exp, vector<string> commands, operators op_table, operators cost) {

    if (op == "while") {
        return new CommandExpression(new LoopCommand(lex_bool_exp, commands, op_table, cost));
    }

    if (op == "if") {
        return new CommandExpression(new IfCommand(lex_bool_exp, commands, op_table, cost));
    }

    return nullptr;
}




void run_scope(operators costs, operators op_table, SymbolTable& var_table, vector<string> to_run) {

    int size = to_run.size();
    for (int i = 0; i < size; i++) {

        vector<string> v = run_shunting_yard(op_table, lexer(to_run[i]));
        Expression* exp = parsing(costs, var_table, v);
        exp->calculate(var_table);
        delete exp;
    }
}