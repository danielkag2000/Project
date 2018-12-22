#ifndef PROJECT_STABLE_H
#define PROJECT_STABLE_H

#include <unordered_map>
#include <string>
#include <list>
#include "data_server.h"

using namespace std;

class Variable {
public:
    /**
     * Get value of this variable
     * @return the value
     */
    virtual double get() = 0;

    /**
     * Update this variable without sending to the server
     * (used when receiving data from server)
     * @param val the new value
     */
    virtual void update(double val) = 0;

    /**
     * Set the inner value of this variable.
     * @param val the new value
     */
    virtual void set(double val) = 0;
};

enum BindType {

    REMOTE_HANDLE,
    LOCAL_VARIABLE
};

class SymbolTable {
private:
    unordered_map<string, Variable*> _vars;
    DataTransfer& _transfer;
public:

    SymbolTable(DataTransfer& transfer) : _transfer(transfer) { }

    /**
     * Query whether a variable exists.
     * @param name the name of the variable
     * @return true if exists, false otherwise.
     */
    bool exists(const string& name);

    /**
     * Bind a variable to another variable or path.
     * @param name the name of the variable to bind
     * @param handle a variable to bind to or a remote handle
     * @param type the type of the bind
     */
    void bind(const string& name, const string& handle, BindType type);

    /**
     * Sets a value of a variable.
     * @param var the variable name
     * @param val the new value
     */
    void set(const string& var, double val);

    /**
     * Get a current value of a variable.
     * @param name the name of the variable
     * @return the value of the variable
     */
    double get(const string& name);

    /**
     * Get all variables as a map.
     */
    unordered_map<string, double> asMap();

    /**
     * Remove a variable from the symbol table
     * @param reference the variable name
     */
    void remove(const string reference);

    /**
     * Get a list of the variable names
     */
    list<string> get_variable_list();

    /**
     * Destructor.
     */
    ~SymbolTable();
};


#endif //PROJECT_STABLE_H
