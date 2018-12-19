#include <iostream>

#include "vars/stable.h"
#include "algorithms/lexer.h"
#include "algorithms/shunting_yard_algorithm.h"

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

    for (string& s : v) {
        cout << s << ", ";
    }
    cout << endl;

    operators ops{ { "+", 1 }, { "-", 1 }, { "*", 2 }, { "/", 2 } };
    vector<string> postfix = run_shunting_yard(ops, v);

    for (string& s : postfix) {
        cout << s << " ";
    }
    cout << endl;

    return 0;
}