#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include <string>
using namespace std;

class ParserIterator;

class Command {
public:
    virtual double doCommand(ParserIterator*) = 0;

    virtual ~Command() { }
};

class ParserIterator {

    /**
     *
     * @return
     */
    virtual Command* getCommand() = 0;
    virtual string getString() = 0;
    virtual double getDouble() = 0;

    virtual bool endOfLine() = 0;
    virtual void next() = 0;

    virtual void clearAllocated() = 0;

    virtual ~ParserIterator() { }
};

#endif
