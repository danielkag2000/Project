#ifndef PROJECT_COMMAND_EXPRESSION_H
#define PROJECT_COMMAND_EXPRESSION_H

#include "command.h"
#include "../exp/exp.h"

class CommandExpression : public Expression {
private:
    Command* _command;

public:
    CommandExpression(Command* com) {
        this->_command = com;
    }

    virtual double calculate(SymbolTable& vars) {
        return this->_command->doCommand(vars);
    }

    virtual string returnValue(SymbolTable& vars) {
        return this->_command->returnValue(vars);
    }

    virtual ~CommandExpression() {
        delete _command;
    }
};

#endif //PROJECT_COMMAND_EXPRESSION_H
