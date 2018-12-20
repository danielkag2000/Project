#ifndef PROJECT_SIMPLE_COMMANDS_H
#define PROJECT_SIMPLE_COMMANDS_H

#include "command.h"
#include "../exceptions.h"

/**
 * create the var command
 */
class VarCommand : public Command {
private:
    string varSymbol;

public:
    VarCommand(string var) {
        this->varSymbol = var;
    }

    virtual double doCommand(SymbolTable& vars) {
        if (vars.exists(this->varSymbol)) {
            throw Exception("var " + this->varSymbol + " has been initialized before!");
        }
        // the parameter has no value yet
        vars.set(this->varSymbol, NAN);
        return NAN; // succeed
    }

    virtual string returnValue(SymbolTable& vars) {
        return this->varSymbol;
    }
};

/**
 * create the bind command
 */
class BindCommand : public Command {
private:
    string varToBind;
    string theBind;

public:
    BindCommand(string varToBind, string theBind) {
        this->varToBind = varToBind;
        this->theBind = theBind;
    }

    virtual double doCommand(SymbolTable& vars) {
        if (!vars.exists(this->varToBind)) {
            throw Exception("var " + this->varToBind + " is not exist!");
        }
        // the parameter has no value yet
        vars.bind(this->varToBind, this->theBind);
        return vars.get(varToBind);  // return not a number
    }

    virtual string returnValue(SymbolTable& vars) {
        return to_string(doCommand(vars));
    }
};

/**
 * create the assign command
 */
class AssignCommand : public Command {
private:
    string assigned;
    double varToAssign;

public:
    AssignCommand(string assigned, double varToAssign) {
        this->assigned = assigned;
        this->varToAssign = varToAssign;
    }

    virtual double doCommand(SymbolTable& vars) {
        if (!vars.exists(this->assigned)) {
            throw Exception("var " + this->assigned + " is not exist!");
        }
        // the parameter has no value yet
        vars.set(this->assigned, this->varToAssign);
        cout<<assigned<<" = "<<varToAssign<<endl;
        return varToAssign;  // succeed
    }

    virtual string returnValue(SymbolTable& vars) {
        return to_string(doCommand(vars));
    }
};

#endif //PROJECT_SIMPLE_COMMANDS_H
