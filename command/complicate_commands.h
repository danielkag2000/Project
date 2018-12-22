#ifndef PROJECT_COMPLICATE_COMMANDS_H
#define PROJECT_COMPLICATE_COMMANDS_H

#include <list>
#include <vector>
#include <cmath>
#include <algorithm>
#include "../algorithms/parsing.h"
#include "../algorithms/lexer.h"
#include "../exp/exp.h"

/**
 * create the loop command
 */
class LoopCommand : public Command {
private:
    vector<string> booleanCondition;
    vector<string> commands;
    operators op_table;
    operators costs;

public:
    LoopCommand(vector<string> booleanCondition, vector<string> commands, operators op_table, operators cost) {
        this->booleanCondition = booleanCondition;
        this->commands = commands;
        this->costs = cost;
        this->op_table = op_table;
    }

    virtual double doCommand(SymbolTable& vars) {
        // get the boolean expression
        Expression* exp = parsing(this->costs, vars, this->booleanCondition);

        // run the commands
        while (exp->calculate(vars)) {
            // run the scope
            run_scope(this->costs, this->op_table, vars, this->commands);
            delete exp;
            // get the boolean expression
            exp = parsing(this->costs, vars, this->booleanCondition);
        }

        delete exp;
        return NAN;
    }

    virtual string returnValue(SymbolTable& vars) {
        return "";
    }
};

/**
 * create the loop command
 */
class IfCommand : public Command {
private:
    vector<string> booleanCondition;
    vector<string> commands;
    operators op_table;
    operators costs;

public:
    IfCommand(vector<string> booleanCondition, vector<string> commands, operators op_table, operators cost) {
        this->booleanCondition = booleanCondition;
        this->commands = commands;
        this->costs = cost;
        this->op_table = op_table;
    }

    virtual double doCommand(SymbolTable& vars) {
        // get the boolean expression
        Expression* exp = parsing(this->costs, vars, this->booleanCondition);

        // run the commands
        if (exp->calculate(vars)) {
            // run the scope
            run_scope(this->costs, this->op_table, vars, this->commands);
        }

        delete exp;
        return NAN;
    }

    virtual string returnValue(SymbolTable& vars) {
        return "";
    }
};

#endif //PROJECT_COMPLICATE_COMMANDS_H
