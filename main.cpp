#include <iostream>
#include <algorithm>
#include <cmath>
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

    operators ops{ { "+", 1 }, { "-", 1 }, { "*", 2 }, { "/", 2 }, { "==", 0 }, { "var", -2 }, { "bind", -2 }, { "=", -2 }, { "=bind", -2 }, { "print", -10 },
                   { "{", -20 }, { "}", -20 }, { "<", 0 }, { ">", 0 }, { "<=", 0 }, { ">=", 0 }, { "sleep", -10 }, { "openDataServer", -10 }};

    operators costs{ { "+", 2 }, { "-", 2 }, { "*", 2 }, { "/", 2 }, { "==", 2 }, { "var", 1 }, { "bind", 2 }, { "=", 2 }, { "=bind", 2 }, { "print", 1 }
                     , { "<", 2 }, { ">", 2 }, { "<=", 2 }, { ">=", 2 }, { "sleep", 1 }, { "openDataServer", 2 }};

    vector<string> multi_line_op = {"while", "if"};
    run_prog(cin, ops, multi_line_op, costs);
    return 0;
}


void run_prog(istream& input, operators op_table, vector<string> multi_line_op, operators cost) {
    string s;
    DataTransfer dt;
    SymbolTable table(dt);

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

            vector<string> v = lexer(s);

            if (find(v.begin(), v.end(), "}") != v.end()) {
                v.erase(find(v.begin(), v.end(), "}"));
                string new_str = "";
                for (string str : v) {
                    new_str += " " + str;
                }

                res.push_back(new_str);
                break;
            }
            res.push_back(s);
        }
    }

    return res;
}