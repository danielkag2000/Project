#include "stable.h"
#include <iostream>

void variable::saveData() {
    cout << "Saved Data!" << endl;
    int x;
}

void variable::retrieveData() {

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