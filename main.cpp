#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include "vars/stable.h"
#include "algorithms/lexer.h"
#include "algorithms/shunting_yard_algorithm.h"
#include "exp/expression_types.h"
#include "exp/exp.h"
#include "algorithms/parsing.h"
#include "exp/expression_map.h"
#include "vars/data_server.h"

using namespace std;

vector<string> read_scope(istream& input);
void run_prog(istream& input, operators& op_table, vector<string> multi_line_op, operators& cost, SymbolTable& table);

int main(int argc, char* argv[]) {

    operators ops{ { "+", 1 }, { "-", 1 }, { "*", 2 }, { "/", 2 }, { "==", 0 }, { "!=", 0 },
                   { "var", -2 }, { "=", -2 }, { "=bind", -2 }, { "print", -10 },
                   { "{", -20 }, { "}", -20 }, { "<", 0 }, { ">", 0 },
                   { "<=", 0 }, { ">=", 0 }, { "sleep", -10 }, { "openDataServer", -10 },
                   { "connect", -10 }, { ",", -1 }};

    operators costs{ { "+", 2 }, { "-", 2 }, { "*", 2 }, { "/", 2 }, { "==", 2 }, { "var", 1 },
                     { "=", 2 }, { "=bind", 2 }, { "print", 1 }, { "!=", 2 },
                     { "<", 2 }, { ">", 2 }, { "<=", 2 }, { ">=", 2 },
                     { "sleep", 1 }, { "openDataServer", 2 }, { "connect", 2}};

    vector<string> multi_line_op = {"while", "if"};

    DataTransfer dt;
    SymbolTable table(dt);


    try {

        if (argc == 2) {
            ifstream f(argv[1]);
            run_prog(f, ops, multi_line_op, costs, table);

        } else {
            run_prog(cin, ops, multi_line_op, costs, table);
        }
    } catch (...) {
        dt.closeAll();
        cout << "an exception has been occur, the program closed" << endl;
    }
    return 0;
}


void run_prog(istream& input, operators& op_table, vector<string> multi_line_op, operators& cost, SymbolTable& table) {
    string s;

    while (getline(input, s)) {
        if (s != "exit") {
            bool is_complicate = false;  // if the line is a complicate expression
            for(string& op : multi_line_op) {
                vector<string> check = lexer(s);
                if (check.empty()) {
                    break;
                }
                if (check[0] == op) {
                    is_complicate = true;
                    check.erase(check.begin());

                    vector<string> lex_bool_exp = check;
                    if (find(lex_bool_exp.begin(), lex_bool_exp.end(), "{") == lex_bool_exp.end()) {
                        throw SyntaxException("expecting '}'");
                    }
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
                vector<string> words;

                for (string& s : v) {
                    if (s != ",") {
                        words.push_back(s);
                    }
                }

                Expression* exp = parsing(cost, table, words);
                if (exp != nullptr) {
                    exp->calculate(table);
                    delete exp;
                }
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
        if (!s.empty()) {
            if (lexer(s)[0] == "}") {
                break;
            }

            vector<string> v = lexer(s);

            if (find(v.begin(), v.end(), "}") != v.end()) {
                v.erase(find(v.begin(), v.end(), "}"));
                string new_str = "";
                for (string& str : v) {
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