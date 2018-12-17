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
    void retrieveData();
public:
    double getValue();
    void setValue(double val);

    void bind(const string& handle);
    void unbind();
    bool bound();
};

class SymbolTable {
private:
    unordered_map<string, Variable> _vars;
public:
    bool exists(const string& name);

    void set(const string& name, double val);
    double get(const string& name);

    void bind(const string& name, const string& handle);
    void unbind(const string& name);
};


#endif //PROJECT_STABLE_H
