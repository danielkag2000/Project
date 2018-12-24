#ifndef PROJECT_COMMAND_CREATOR_H
#define PROJECT_COMMAND_CREATOR_H

#include <vector>
#include "../exp/exp.h"
#include "../definitions.h"
#include <string>

class CommandCreator {
protected:
    SymbolTable& var_table;

public:
    CommandCreator(SymbolTable& var_table) : var_table(var_table) {};
    virtual Expression* create(vector<string>) = 0;
};

class PlusCreator : public CommandCreator {
public:
    PlusCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class MinusCreator : public CommandCreator {
public:
    MinusCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class MulCreator : public CommandCreator {
public:
    MulCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class DivCreator : public CommandCreator {
public:
    DivCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class EquCreator : public CommandCreator {
public:
    EquCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class NotEquCreator : public CommandCreator {
public:
    NotEquCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class VarCreator : public CommandCreator {
public:
    VarCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class BindCreator : public CommandCreator {
public:
    BindCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class AssignCreator : public CommandCreator {
public:
    AssignCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class PrintCreator : public CommandCreator {
public:
    PrintCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class GreatCreator : public CommandCreator {
public:
    GreatCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class LessCreator : public CommandCreator {
public:
    LessCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class GreatEquCreator : public CommandCreator {
public:
    GreatEquCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class LessEquCreator : public CommandCreator {
public:
    LessEquCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class SleepCreator : public CommandCreator {
public:
    SleepCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class ODSCreator : public CommandCreator {
public:
    ODSCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class ConnectCreator : public CommandCreator {
public:
    ConnectCreator(SymbolTable& var_table) : CommandCreator(var_table) {};
    virtual Expression* create(vector<string>);
};

class WhileCreator : public CommandCreator {
private:
    vector<string> multi_line_commands;
    operators op_table;
    operators cost;

public:
    WhileCreator(vector<string> multi_line_commands, operators op_table, operators cost, SymbolTable& var_table)
                 : CommandCreator(var_table) {
        this->multi_line_commands = multi_line_commands;
        this->op_table = op_table;
        this->cost = cost;
    }
    virtual Expression* create(vector<string>);
};

class IfCreator : public CommandCreator {
private:
    vector<string> multi_line_commands;
    operators op_table;
    operators cost;

public:
    IfCreator(vector<string> multi_line_commands, operators op_table, operators cost, SymbolTable& var_table)
              : CommandCreator(var_table) {
        this->multi_line_commands = multi_line_commands;
        this->op_table = op_table;
        this->cost = cost;
    }
    virtual Expression* create(vector<string>);
};

#endif //PROJECT_COMMAND_CREATOR_H
