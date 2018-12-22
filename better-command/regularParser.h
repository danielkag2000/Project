#ifndef PROJECT_REGULARPARSER_H
#define PROJECT_REGULARPARSER_H

#include <iostream>
#include <vector>
#include "command.h"

using namespace std;

class RegularParser : public ParserIterator {
private:
    istream& _is;

    vector<string> _line;
    int _lastRead;
    int _offset;

    void nextLine();

    void nextIfNeeded();
public:
    RegularParser(istream& is) : _is(is) {
        nextLine();
    }

    virtual char getChar();
    virtual string getString();
    virtual double getDouble();

    virtual bool endOfLine();

    virtual void next();
};

#endif
