#ifndef PROJECT_SERVER_COMMAND_H
#define PROJECT_SERVER_COMMAND_H

#include "command.h"
#include <thread>
#include <chrono>
#include <cmath>

/**
 * make the program sleep
 */
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

/**
 * open the data server
 */
class OpenDataServerCommand : public Command {
private:
    int port;
    int rate;

public:
    OpenDataServerCommand(int port, int rate) {
        this->port = port;
        this->rate = rate;
    }

    virtual double doCommand(SymbolTable& vars) {
        vars.getTransfer().openDataServer(this->port, this->rate);
        return NAN;
    }

    virtual string returnValue(SymbolTable& vars) {
        return "";
    }
};

/**
 * connect to the server
 */
class ConnectCommand : public Command {
private:
    string ip;
    int port;

public:
    ConnectCommand(string ip, int port) {
        this->port = port;
        this->ip = ip;
    }

    virtual double doCommand(SymbolTable& vars) {
        vars.getTransfer().openSender(this->port, this->ip);
        return NAN;
    }

    virtual string returnValue(SymbolTable& vars) {
        return "";
    }
};

#endif //PROJECT_SERVER_COMMAND_H
