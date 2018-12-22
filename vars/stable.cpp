#include "stable.h"
#include "../exceptions.h"
#include <iostream>

class NormalVar : public Variable {
private:
    double _value;
public:
    virtual double get() { return _value; }

    virtual void set(double val) { _value = val; }

    virtual void update(double val) { _value = val; }
};

class RemoteBoundVariable : public Variable {
private:
    DataTransfer& _transfer;
    string _bind;
public:
    RemoteBoundVariable(DataTransfer& transfer, const string& bind) :
            _transfer(transfer), _bind(bind) {
    }

    virtual double get() {
        return _transfer.getValue(_bind);
    }

    // shouldn't update, only set
    virtual void update(double d) { }

    virtual void set(double val) {
        _transfer.setValue(_bind, val);
    }
};

class VarBind : public Variable {
private:
    Variable& _bound;

public:
    VarBind(Variable* v) : _bound(*v) { }

    virtual double get() { return _bound.get(); }
    virtual void update(double val) { _bound.update(val); }
    virtual void set(double val) { _bound.set(val); }
};

bool SymbolTable::exists(const string& name) {
    int count = _vars.count(name);
    return count > 0;
}

void SymbolTable::set(const string &var, double val) {
    if (_vars[var] == nullptr) {
        _vars[var] = new NormalVar();
        _allocated.push_back(_vars[var]);
    }

    _vars[var]->set(val);
}

double SymbolTable::get(const string &name) {
    return _vars[name]->get();
}

void SymbolTable::bind(const string &name,
        const string &handle, BindType type) {
    Variable* inserted;

    switch(type) {
        case LOCAL_VARIABLE: {
            // set a new variable bound to variable 'handle'
            inserted = new VarBind(_vars[handle]);
            break;
        }
        case REMOTE_HANDLE: {
            // bind as a remote variable
            inserted = new RemoteBoundVariable(_transfer, handle);
            break;
        }
        default: {
            return;
        }
    }

    _vars[name] = inserted;
    _allocated.push_back(inserted);
}

unordered_map<string, double> SymbolTable::asMap() {
    unordered_map<string, double> map;

    // insert all pairs
    for (auto& varPair : _vars) {
        map.insert({ varPair.first, varPair.second->get() });
    }

    return map;
}

void SymbolTable::remove(const string& name) {
    _vars.erase(name);
}

DataTransfer& SymbolTable::getTransfer() {
    return _transfer;
}

list<string> SymbolTable::get_variable_list() {
    list<string> vars;

    for (auto& varPair : _vars) {
        vars.push_back(varPair.first);
    }

    return vars;
}

SymbolTable::~SymbolTable() {
    // free all memory
    for (auto& var : _allocated) {
        delete var;
    }

    // clear the vars map and allocated list
    _vars.clear();
    _allocated.clear();
}