#include "regularParser.h"
#include "../algorithms/lexer.h"
#include <string>

void RegularParser::nextLine() {
    string ln;
    getline(_is, ln);

    _line = lexer(ln);
    _offset = 0;
    _lastRead = 0;
}

void RegularParser::nextIfNeeded() {
    if (endOfLine()) {
        nextLine();
    }
}

char RegularParser::getChar() {
    return _line[_offset][0];
}

bool RegularParser::endOfLine() {
    return _offset == _line.size();
}

void RegularParser::next() {
    if (endOfLine()) {
        nextLine();
    }
    else {
        _offset += _lastRead;
    }
}


double RegularParser::getDouble() {

}

string RegularParser::getString() {
    _lastRead = 1;
    return _line[_offset];
}