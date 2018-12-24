#ifndef PROJECT_COMMANDS_H
#define PROJECT_COMMANDS_H

#include "command.h"
#include "../vars/stable.h"
#include "../exceptions.h"
#include <iostream>
#include "../utils.h"

/* the simple commands */
class VarCommand : Command {
public:
    VarCommand() {}
    virtual double doCommand(ParserIterator* par_it, SymbolTable& vars);
};

class BindCommand : Command {
public:
    BindCommand() {}
    virtual double doCommand(ParserIterator* par_it, SymbolTable& vars);
};


class AssignCommand : Command {
public:
    AssignCommand() {}
    virtual double doCommand(ParserIterator* par_it, SymbolTable& vars);
};

class PrintCommand : Command {
private:
    ostream& _print_to;
public:
    PrintCommand(ostream& os) : _print_to(os) {}
    virtual double doCommand(ParserIterator* par_it, SymbolTable& vars);
};

class SleepCommand : Command {
public:
    SleepCommand() {}
    virtual double doCommand(ParserIterator* par_it, SymbolTable& vars);
};

/* the server commands */

class OpenDataServerCommand : Command {
private:
    DataTransfer& _dt;
public:
    OpenDataServerCommand(DataTransfer& dt) : _dt(dt) {}
    virtual double doCommand(ParserIterator* par_it, SymbolTable& vars);
};


#endif //PROJECT_COMMANDS_H
