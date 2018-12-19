#include "parsing.h"
#include <stack>
#include "../exceptions.h"

command parsing(operators op_table, SymbolTable var_table, vector<string> tokens) {
    //the parameters to the function
    vector<string> parameters;
    // the "numbers are the non operators
    stack<string> numbers;
    int number_of_tokens = tokens.size();

    for(int i = 0; i < parm_num; i++) {
        string& token = tokens[i];
        // if it is not an operator
        if (op_table.find(token) == op_table.end()) {
            numbers.push(token);

        } else { // it is an operator
            int parm_num = op_table[token];
            for (int j = 0; j < parm_num; j++) {
                if (numbers.empty()) {
                    throw SyntaxException("too few parameters")
                }
                parameters.push_back(numbers.top())
                numbers.pop()
            }


        }
    }
    return NULL;
}