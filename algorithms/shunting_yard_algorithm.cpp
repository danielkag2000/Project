#include "shunting_yard_algorithm.h"
#include <queue>
#include <stack>

vector<string> run_shunting_yard(operators op_map, vector<string> tokens){

    // "number" is a non operator
    queue<string> _numbers;
    // the operators
    stack<string> _operators;
    // the result
    vector<string> result;

    // read all the tokens
    for (string& token: tokens) {
        // if the token is number
        if (token == "(") {
            _operators.push(token);

        } else if (token == ")") {
            while (_operators.top() != "(" && !_operators.empty()) {
                _numbers.push(_operators.top());
                _operators.pop();
            }
            // there is no ")" so there is a problem
            if (_operators.empty()) {
                throw InvalidParenthesisOrder();
            }
            _operators.pop();

        // is an operator
        } else if (op_map.find(token) == op_map.end()) {
            _numbers.push(token);

        } else {  // is an operator from the list
            // while there is an operator at the top of the stack with greater precedence
            while (!_operators.empty() && (op_map[token] < op_map[_operators.top()])) {
                _numbers.push(_operators.top());
                _operators.pop();
            }
            _operators.push(token);
        }
    }  // end of the for loop

    // while there is an operator at the top of the
    while (!_operators.empty()) {
        _numbers.push(_operators.top());
        _operators.pop();
    }

    // get all the values to the result
    while (!_numbers.empty()) {
        result.push_back(_numbers.front());
        _numbers.pop();
    }

    // check the parenthesis
    for (string& s : result) {
        if (s == "(" || s == ")") {
            throw InvalidParenthesisOrder();
        }
    }

    return result;
}
