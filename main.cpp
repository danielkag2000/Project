#include <iostream>

#include "vars/stable.h"

using namespace std;

int main() {
    SymbolTable table;
    table.set("hello", 4.3);
    table.bind("hello", "fuck/you");
    table.set("hello", 4.5);

    cout << table.get("hello") << endl;
    cout << sizeof(string) << endl;
    return 0;
}