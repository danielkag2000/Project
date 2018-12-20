#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include "../vars/stable.h"
#include <vector>

using namespace std;

class Command {

public:
    virtual double doCommand(SymbolTable& vars) = 0;

    virtual string returnValue(SymbolTable& vars) = 0;

    virtual ~Command() {}
};

#endif //PROJECT_COMMAND_H
