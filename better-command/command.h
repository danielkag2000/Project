#ifndef PROJECT_COMMAND_H
#define PROJECT_COMMAND_H

#include <string>
#include "../vars/stable.h"
using namespace std;

class ParserIterator;

class Command {
public:
    virtual double doCommand(ParserIterator*, SymbolTable*) = 0;

    virtual ~Command() { }
};

class ParserIterator {
public:

    virtual char getChar() = 0;

    /**
     * Get current command.
     * @return a command
     */
    virtual Command* getCommand() = 0;

    /**
     * Get current string.
     * @return a string
     */
    virtual string getString() = 0;

    /**
     * Get current double.
     * @return a double
     */
    virtual double getDouble() = 0;

    /**
     * Query whether this is the end of line.
     * @return true if it is, false otherwise.
     */
    virtual bool endOfLine() = 0;

    /**
     * Move to next variable after this one was read.
     */
    virtual void next() = 0;

    /**
     * Save the last read under key.
     * @param name the key to save under
     */
    virtual void save(string& name) = 0;

    /**
     * Get the command saved under key.
     * @param name the key
     * @return
     */
    virtual Command* getCommand(string& name) = 0;


    /**
     *
     * @param name
     * @return
     */
    virtual string getString(string& name) = 0;


    /**
     *
     * @param name
     * @return
     */
    virtual double getDouble(string& name) = 0;

//    virtual void clearAllocated() = 0;

    virtual ~ParserIterator() { }
};

#endif
