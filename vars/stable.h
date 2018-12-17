#ifndef PROJECT_STABLE_H
#define PROJECT_STABLE_H

#include <unordered_map>
#include <string>

using namespace std;

class Variable {
private:
    double _val;
    string _handle;
public:
    double getValue();
    void setValue(double val);

    void bind(const string& handle);
    void unbind();
};

class symbol_table {
    using namespace std;
private:
    unordered_map<string, Variable> _vals;
public:
    void set(const string& name, double val);
    double get(const string& name);
};


#endif //PROJECT_STABLE_H
