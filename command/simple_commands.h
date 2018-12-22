#ifndef PROJECT_SIMPLE_COMMANDS_H
#define PROJECT_SIMPLE_COMMANDS_H

#include <cmath>
#include "command.h"
#include "../exceptions.h"
#include "../utils.h"

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
            throw SyntaxException(this->varToBind + " does not exist.");
        }

        if (this->theBind[0] == '\"') {
            // given "str" print str
            string path = this->theBind.substr(1, this->theBind.size() - 2);
            vars.bind(this->varToBind, path, BindType::REMOTE_HANDLE);

        } else { // is a variable
            if (vars.exists(this->theBind)) {
                vars.bind(this->varToBind, this->theBind, BindType::LOCAL_VARIABLE);

            } else {  // this is exception
                throw Exception("this variable is not exist");
            }
        }
        return vars.get(this->varToBind);  // return not a number
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
        return varToAssign;  // succeed
    }

    virtual string returnValue(SymbolTable& vars) {
        return to_string(doCommand(vars));
    }
};

/**
 * create the print command
 */
class PrintCommand : public Command {
private:
    string varVal;

public:
    PrintCommand(string var) {
        this->varVal = var;
    }

    virtual double doCommand(SymbolTable& vars) {

        if (this->varVal[0] == '\"') {
            // given "str" print str
            cout << this->varVal.substr(1, this->varVal.size() - 2) << endl;

        } else if (isNumber(this->varVal)) {  // is a number
            cout << stod(this->varVal) << endl;

        } else { // is a variable
            if (vars.exists(this->varVal)) {
                cout << vars.get(this->varVal) << endl;

            } else {  // this is exception
                throw Exception("this variable is not exist");
            }
        }
        return NAN;
    }

    virtual string returnValue(SymbolTable& vars) {
        return "";
    }
};


#endif //PROJECT_SIMPLE_COMMANDS_H
