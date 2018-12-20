#ifndef PROJECT_PARSING_H
#define PROJECT_PARSING_H

#include "../command/command.h"
#include "../command/command_expression.h"
#include "../vars/stable.h"
#include "../definitions.h"
#include <vector>

Expression* parsing(operators op_table, SymbolTable& var_table, vector<string> tokens);

Expression* parser(vector<string> parameters, SymbolTable& var_table, string func_operator);

Expression* parser_complicate(string op, vector<string> lex_bool_exp, vector<string> commands, operators op_table, operators cost);

void run_scope(operators costs, operators op_table, SymbolTable& var_table, vector<string> to_run);



#endif //PROJECT_PARSING_H
