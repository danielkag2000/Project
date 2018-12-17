#ifndef PROJECT_STABLE_H
#define PROJECT_STABLE_H

#include <unordered_map>
#include <string>

using namespace std;

class variable {
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
};

class symbol_table {
private:
    unordered_map<string, variable> _vars;
public:
    void set(const string& name, double val);
    double get(const string& name);

    void bind(const string& name, const string& handle);
    void unbind(const string& name);
};


#endif //PROJECT_STABLE_H
