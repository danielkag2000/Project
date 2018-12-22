#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include <string>
#include "../vars/stable.h"
using namespace std;

class ParserIterator;

class Command {
public:
    virtual double doCommand(ParserIterator*) = 0;

    virtual ~Command() { }
};

class ParserIterator {

    /**
     * Get current command.
     * @return a command
     */
    virtual Command* getCommand() = 0;

    /**
     * Get current string.
     * @return
     */
    virtual string getString() = 0;
    virtual double getDouble() = 0;

    virtual bool endOfLine() = 0;
    virtual void next() = 0;

    virtual void breakpoint() = 0;
    virtual void goBreakpoint() = 0;

    virtual void clearAllocated() = 0;

    virtual ~ParserIterator() { }
};

#endif
