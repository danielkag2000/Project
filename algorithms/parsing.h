#ifndef PROJECT_PARSING_H
#define PROJECT_PARSING_H

#include "../command/command.h"
#include "../vars/stable.h"
#include "../definitions.h"
#include <vector>

command parsing(operators op_table, SymbolTable var_table, vector<string> tokens);

command parser(vector<string> parameters, SymbolTable var_table, string func_operator)

#endif //PROJECT_PARSING_H
