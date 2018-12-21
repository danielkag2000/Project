#ifndef PROJECT_PARSING_H
#define PROJECT_PARSING_H

#include "../command/command.h"
#include "../exp/command_expression.h"
#include "../vars/stable.h"
#include "../definitions.h"
#include <vector>

/**
 * the parser of the strings
 * @param op_table a table of the operators and the number of parameters each
 *                 one need
 * @param var_table the Symbol Table
 * @param tokens the line after running lexer and shunting yard
 * @return the Expression of the line
 */
Expression* parsing(operators op_table, SymbolTable& var_table, vector<string> tokens);

/**
 * the parser take the function and its parameters and create from it an Expression
 * @param parameters the parameters (as string) of the function
 * @param var_table the Symbol Table
 * @param func_operator the function name
 * @return the Expression of the function
 */
Expression* parser(vector<string> parameters, SymbolTable& var_table, string func_operator);

/**
 * a parser of an complicate Expression (a multi line expression)
 * @param op the name of the operator
 * @param lex_bool_exp the boolean condition
 * @param commands the lines of the expression
 * @param op_table the table of operators with the priority of each one
 * @param cost a table of the operators and the number of parameters each
 *                 one need
 * @return the Expression of the lines
 */
Expression* parser_complicate(string op, vector<string> lex_bool_exp, vector<string> commands, operators op_table, operators cost);

/**
 * run a scope
 * @param costs a table of the operators and the number of parameters each
 *                 one need
 * @param op_table the table of operators with the priority of each one
 * @param var_table the Symbol Table
 * @param to_run the lines to run
 */
void run_scope(operators costs, operators op_table, SymbolTable& var_table, vector<string> to_run);



#endif //PROJECT_PARSING_H
