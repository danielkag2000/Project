#ifndef PROJECT_CREATE_CREATORS_MAP_H
#define PROJECT_CREATE_CREATORS_MAP_H

#include "../definitions.h"
#include <unordered_map>
#include "command_creator.h"

using namespace std;

unordered_map<string, CommandCreator> create_creators_map(vector<string> multi_line_commands, operators op_table, operators cost, SymbolTable& var_table) {
    unordered_map<string, CommandCreator> table {{"+", PlusCreator(var_table)}, {"-", MinusCreator(var_table)},
                                                 {"*", MulCreator(var_table)}, {"/", MinusCreator(var_table)},
                                                 {"==", EquCreator(var_table)}, {"!=", DivCreator(var_table)},
                                                 {"var", VarCreator(var_table)}, {"=bind", BindCreator(var_table)},
                                                 {"=", AssignCreator(var_table)}, {"print", PrintCreator(var_table)},
                                                 {">", GreatCreator(var_table)}, {"<", LessCreator(var_table)},
                                                 {">=", GreatEquCreator(var_table)}, {"<=", LessEquCreator(var_table)},
                                                 {"sleep", SleepCreator(var_table)}, {"openDataServer", ODSCreator(var_table)},
                                                 {"connect", ConnectCreator(var_table)},
                                                 {"while", WhileCreator(multi_line_commands, op_table, cost, var_table)},
                                                 {"if", IfCreator(multi_line_commands, op_table, cost, var_table)}};

    return table;
}

#endif //PROJECT_CREATE_CREATORS_MAP_H
