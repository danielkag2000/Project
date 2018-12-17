#include "stable.h"
#include <iostream>

void variable::saveData() {
    cout << "Saved Data!" << endl;
}

void variable::retrieveData() {
    cout << "Retrieved data from server!" << endl;
}

void variable::bind(const string &handle) {
    _handle = handle;

    if (!handle.empty()) {
        retrieveData();
    }
}

void variable::unbind() {
    _handle = "";
}

double variable::getValue() {
    retrieveData();
    return _val;
}

void variable::setValue(double val) {
    _val = val;
    saveData();
}

void symbol_table::unbind(const string &name) {

}