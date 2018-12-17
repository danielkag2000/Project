#include <iostream>

#include "vars/stable.h"

using namespace std;

int main() {
    SymbolTable table;
    table.set("hello", 4.3);
    table.bind("hello", "fuck/you");
    return 0;
}