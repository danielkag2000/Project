#ifndef PROJECT_SHUNTING_YARD_ALGORITHM_H
#define PROJECT_SHUNTING_YARD_ALGORITHM_H

#include <list>
#include <vector>
#include <string>
#include <unordered_map>
#include "../exceptions.h"
#include "../definitions.h"

using namespace std;

/**
 * the Shunting Yard algorithm
 * @param operators the map of operators and there precedence
 * @param tokens the tokens of the lines
 * @return a vector<string> in postfix order
 */
vector<string> run_shunting_yard(operators op_map, vector<string> tokens);

#endif //PROJECT_SHUNTING_YARD_ALGORITHM_H