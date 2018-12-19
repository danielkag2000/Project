#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include "../vars/stable.h"
#include <vector>

class command {

public:
    double doCommand(SymbolTable var_table, vector<string> tokens) = 0;
};

#endif //PROJECT_COMMAND_H
