#ifndef PROJECT_COMMAND_EXPRESSION_H
#define PROJECT_COMMAND_EXPRESSION_H

#include "../command/command.h"
#include "exp.h"

class CommandExpression : public Expression {
private:
    command* _command;

public:
    CommandExpression(command* com) {
        this->_command = com;
    }

    virtual double calculate(variables assignment) {
        return this->_command->doCommand();
    }

    virtual ~CommandExpression() {
        delete _command;
    }
};

#endif //PROJECT_COMMAND_EXPRESSION_H
