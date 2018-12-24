#ifndef PROJECT_CREATE_CREATORS_MAP_H
#define PROJECT_CREATE_CREATORS_MAP_H

#include "../definitions.h"
#include <unordered_map>
#include "command_creator.h"

using namespace std;

unordered_map<string, CommandCreator*> create_creators_map(vector<string> multi_line_commands, operators op_table, operators cost, SymbolTable& var_table) {
    unordered_map<string, CommandCreator*> table {
        {"+", new PlusCreator(var_table)}, {"-", new MinusCreator(var_table)},
        {"*", new MulCreator(var_table)}, {"/", new MinusCreator(var_table)},
        {"==", new EquCreator(var_table)}, {"!=", new DivCreator(var_table)},
        {"var", new VarCreator(var_table)}, {"=bind", new BindCreator(var_table)},
        {">", new GreatCreator(var_table)}, {"<", new LessCreator(var_table)},
        {">=", new GreatEquCreator(var_table)}, {"<=", new LessEquCreator(var_table)},
        {"=", new AssignCreator(var_table)}, {"print", new PrintCreator(var_table)},
        {"sleep", new SleepCreator(var_table)}, {"openDataServer", new ODSCreator(var_table)},
        {"connect", new ConnectCreator(var_table)},
        {"while", new WhileCreator(multi_line_commands, op_table, cost, var_table)},
        {"if", new IfCreator(multi_line_commands, op_table, cost, var_table)}
    };

    return table;
}

#endif //PROJECT_CREATE_CREATORS_MAP_H
