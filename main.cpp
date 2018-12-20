#include <iostream>

#include "vars/stable.h"
#include "algorithms/lexer.h"
#include "algorithms/shunting_yard_algorithm.h"
#include "exp/expression_types.h"
#include "exp/exp.h"
#include "algorithms/parsing.h"
#include "exp/expression_map.h"


using namespace std;

vector<string> read_scope(istream& input);
void run_prog(istream& input, operators op_table, vector<string> multi_line_op, operators cost);

int main() {
    /*SymbolTable table;
    table.set("hello", 7);
    table.bind("hello", "fuck/you");
    //table.set("x", 4.5);
    //table.set("y", 100);
    //table.set("z", 5);

    cout << table.get("hello") << endl;
    cout << sizeof(string) << endl;

    string str;
    getline(cin, str);

    vector<string> v = lexer(str);
    //vector<string> v = {"x", "+","y","*","(","z","==","5", ")","-","(","-3",")"};
    //vector<string> v = {"x", "=","50"};
    for (string& s : v) {
        cout << s << ", ";
    }
    cout << endl;

    operators ops{ { "+", 1 }, { "-", 1 }, { "*", 2 }, { "/", 2 }, { "==", 0 }, { "var", -2 }, { "bind", -2 }, { "=", -2 }, { "=bind", -2 }, { "print", -10 } };
    cout << "running boi" << endl;
    vector<string> postfix = run_shunting_yard(ops, v);
    cout << "finished running" << endl;

    for (string& s : postfix) {
        cout << s << " ";
    }
    cout << endl;
    operators op_table{ { "+", 2 }, { "-", 2 }, { "*", 2 }, { "/", 2 }, { "==", 2 }, { "var", 1 }, { "bind", 2 }, { "=", 2 }, { "=bind", 2 }, { "print", 1 } };
    Expression *e = parsing(op_table, table, postfix);

    cout << "should be:  " << e->calculate(table)<<endl;
    //table.bind("x", "hello");
    //cout<<"hello is: " << table.get("hello")<<endl;
    cout<<"x is: " << table.get("x")<<endl;
    //table.set("x", - 50);
    //cout<<"hello is: " << table.get("hello")<<endl;*/


    operators ops{ { "+", 1 }, { "-", 1 }, { "*", 2 }, { "/", 2 }, { "==", 0 }, { "var", -2 }, { "bind", -2 }, { "=", -2 }, { "=bind", -2 }, { "print", -10 },
                   { "{", -20 }, { "}", -20 }, { "<", 0 }, { ">", 0 }, { "<=", 0 }, { ">=", 0 }};

    operators costs{ { "+", 2 }, { "-", 2 }, { "*", 2 }, { "/", 2 }, { "==", 2 }, { "var", 1 }, { "bind", 2 }, { "=", 2 }, { "=bind", 2 }, { "print", 1 }
                     , { "<", 2 }, { ">", 2 }, { "<=", 2 }, { ">=", 2 }};

    vector<string> multi_line_op = {"while", "if"};
    run_prog(cin, ops, multi_line_op, costs);

    return 0;
}


void run_prog(istream& input, operators op_table, vector<string> multi_line_op, operators cost) {
    string s;
    SymbolTable table;

    while (getline(input, s)) {
        if (s != "") {
            bool is_complicate = false;  // if the line is a complicate expression
            for(string& op : multi_line_op) {
                vector<string> check = lexer(s);

                if (check[0] == op) {
                    is_complicate = true;
                    check.erase(check.begin());

                    vector<string> lex_bool_exp = check;
                    lex_bool_exp.erase(find(lex_bool_exp.begin(), lex_bool_exp.end(), "{"));

                    // make post-fix
                    lex_bool_exp = run_shunting_yard(op_table, lex_bool_exp);
                    // get the commands after the "{" until encounter "}"
                    vector<string> commands = read_scope(input);
                    // make the complicate expression
                    Expression* exp = parser_complicate(op, lex_bool_exp, commands, op_table, cost);
                    exp->calculate(table);
                    delete exp;

                    break;
                }
            }

            if (!is_complicate) {  // it is a expression in 1 line

                vector<string> v = run_shunting_yard(op_table, lexer(s));
                Expression* exp = parsing(cost, table, v);
                exp->calculate(table);
                delete exp;
            }

        } else {
            break;
        }
    }
}


vector<string> read_scope(istream& input) {
    string s;
    vector<string> res;
    while (getline(input, s)) {
        if (s != "") {
            if (s == "}") {
                break;
            }
            res.push_back(s);
        }
    }

    return res;
}