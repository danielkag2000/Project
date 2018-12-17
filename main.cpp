#include <iostream>

#include "vars/stable.h"
#include "algorithms/lexer.h"

using namespace std;

int main() {
    SymbolTable table;
    table.set("hello", 4.3);
    table.bind("hello", "fuck/you");
    table.set("hello", 4.5);

    cout << table.get("hello") << endl;
    cout << sizeof(string) << endl;



    string str;
    getline(cin, str);

    vector<string> v = lexer(str);

    for(string &s : v) {
        cout << s << endl;
    }

    return 0;
}