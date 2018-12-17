#ifndef PROJECT_STABLE_H
#define PROJECT_STABLE_H

#include <unordered_map>
#include <string>

using namespace std;

class Variable {
private:
    double _val;
    string _handle;

    void saveData();
public:
    /**
     * Get value of this variable
     * @return the value
     */
    double get();

    /**
     * Update the inner value of this variable without sending to server.
     * @param val the new value
     */
    void update(double val);

    /**
     * Set the inner value of this variable, and send to server.
     * @param val the new value
     */
    void set(double val);

    /**
     * Bind this variable to a given handle.
     * @param handle
     */
    void bind(const string& handle);

    /**
     * Unbind this variable.
     */
    void unbind();

    /**
     * Query whether this variable is bound.
     * @return true if it is.
     */
    bool bound();
};

class SymbolTable {
private:
    unordered_map<string, Variable> _vars;
public:
    void bind(const string& name, const string& handle);
    void unbind(const string& name);

    void update(const string& var, double newVal);
    void set(const string& var, double val);

    double get(const string& name);
};


#endif //PROJECT_STABLE_H
