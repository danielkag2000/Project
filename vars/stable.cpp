#include "stable.h"
#include <iostream>


void Variable::saveData() {
    if (bound()) {
        cout << "Saved Data!" << endl;
    }
}

void Variable::retrieveData() {
    if (bound()) {
        cout << "Retrieved data from server!" << endl;
    }
}

bool Variable::bound() {
    return !_handle.empty();
}

void Variable::bind(const string &handle) {
    _handle = handle;
    retrieveData();
}

void Variable::unbind() {
    _handle = "";
}

double Variable::getValue() {
    retrieveData();
    return _val;
}

void Variable::setValue(double val) {
    _val = val;
    saveData();
}

void SymbolTable::bind(const string &name, const string &handle) {
    _vars[name].bind(handle);
}

void SymbolTable::unbind(const string &name) {
    _vars[name].unbind();
}

void SymbolTable::set(const string &name, double val) {
    _vars[name].setValue(val);
}

double SymbolTable::get(const string &name) {
    return _vars[name].getValue();
}