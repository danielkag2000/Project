#ifndef PROJECT_SERVER_COMMAND_H
#define PROJECT_SERVER_COMMAND_H

#include "command.h"
#include <thread>
#include <chrono>

class SleepCommand : public Command {
private:
    int millisec;

public:
    SleepCommand(int sleepFor) {
        this->millisec = sleepFor;
    }

    virtual double doCommand(SymbolTable& vars) {
        this_thread::sleep_for(chrono::milliseconds(this->millisec));
        return NAN;
    }

    virtual string returnValue(SymbolTable& vars) {
        return "";
    }
};

#endif //PROJECT_SERVER_COMMAND_H
