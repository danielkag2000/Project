#include "commands.h"
#include <cmath>


/* the server commands */

double OpenDataServerCommand::doCommand(ParserIterator* par_it, SymbolTable& vars) {
    if (par_it->endOfLine()) {
        throw SyntaxException("not enough arguments!");
    }

    // the port value
    double val = par_it->getDouble();

    // if is not an int
    if (val != (int)val) {
        throw SyntaxException("expected an int");
    }

    int port = (int)val;

    // check if there is an parameter
    par_it->next();
    if (par_it->endOfLine()) {
        throw SyntaxException("not enough arguments!");
    }

    // the rate value
    val = par_it->getDouble();

    // if is not an int
    if (val != (int)val) {
        throw SyntaxException("expected an int");
    }

    int rate = (int)val;

    par_it->next();
    // more parameters then needed
    if (!par_it->endOfLine()) {
        throw SyntaxException("too many arguments!");
    }

    // open the server
    this->_dt.openDataServer(port, rate);
    return NAN;
}