#include "commands.h"
#include <cmath>

/* the simple commands */

double VarCommand::doCommand(ParserIterator* par_it, SymbolTable& vars) {
    if (par_it->endOfLine()) {
        throw SyntaxException("not enough arguments!");
    }

    string param = par_it->getString();

    if (!isVariable(param)) {
        throw SyntaxException("not a valid name");
    }
    // if exists
    if (vars.exists(param)) {
        throw Exception("variable already exists");
    }

    par_it->next();
    // more parameters then needed
    if (!par_it->endOfLine()) {
        throw SyntaxException("too many arguments!");
    }

    // add to table
    vars.set(param, NAN);

    return NAN;
}


double BindCommand::doCommand(ParserIterator* par_it, SymbolTable& vars) {
    if (par_it->endOfLine()) {
        throw SyntaxException("not enough arguments!");
    }

    // the left value
    string left = par_it->getString();

    // check if there is an parameter
    par_it->next();
    if (par_it->endOfLine()) {
        throw SyntaxException("not enough arguments!");
    }

    // the right value
    string right = par_it->getString();

    par_it->next();
    // more parameters then needed
    if (!par_it->endOfLine()) {
        throw SyntaxException("too many arguments!");
    }

    // the binding
    // it is a string as "string"
    if (par_it->getChar() == '\"') {
        // remove the '\"'
        right = right.substr(1, right.size() - 2);
        vars.bind(left, right, BindType::REMOTE_HANDLE);

    } else { // it is variable
        if (vars.exists(right)) { // if the variable exist
            vars.bind(left, right, BindType::LOCAL_VARIABLE);

        } else {
            throw Exception("variable not found");
        }
    }

    return vars.get(left);
}




double AssignCommand::doCommand(ParserIterator* par_it, SymbolTable& vars) {
    if (par_it->endOfLine()) {
        throw SyntaxException("not enough arguments!");
    }

    // the left value
    string left = par_it->getString();

    // check if there is an parameter
    par_it->next();
    if (par_it->endOfLine()) {
        throw SyntaxException("not enough arguments!");
    }

    // the right value
    double right = par_it->getDouble();

    par_it->next();
    // more parameters then needed
    if (!par_it->endOfLine()) {
        throw SyntaxException("too many arguments!");
    }

    // set the value
    vars.set(left, right);

    return vars.get(left);
}



double PrintCommand::doCommand(ParserIterator* par_it, SymbolTable& vars) {
    if (par_it->endOfLine()) {
        throw SyntaxException("not enough arguments!");
    }

    string to_print;

    // it is a string as "string"
    if (par_it->getChar() == '\"') {
        to_print = par_it->getString();
        // remove the '\"'
        to_print = to_print.substr(1, to_print.size() - 2);

    } else { // it is an computable expression
        to_print = to_string(par_it->getDouble());
    }

    par_it->next();
    // more parameters then needed
    if (!par_it->endOfLine()) {
        throw SyntaxException("too many arguments!");
    }
    // printing
    this->_print_to << to_print;

    return NAN;
}



double SleepCommand::doCommand(ParserIterator* par_it, SymbolTable& vars) {
    if (par_it->endOfLine()) {
        throw SyntaxException("not enough arguments!");
    }

    int mil_sec = par_it->getDouble();

    par_it->next();
    // more parameters then needed
    if (!par_it->endOfLine()) {
        throw SyntaxException("too many arguments!");
    }
    // sleeping
    this_thread::sleep_for(chrono::milliseconds(mil_sec));
    return NAN;
}