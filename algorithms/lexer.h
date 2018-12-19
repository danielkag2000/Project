#ifndef PROJECT_LEXER_H
#define PROJECT_LEXER_H

#include <vector>
#include <string>

#include "definitions.h"

using namespace std;

/***
 * Divide a line to an array of words.
 * @param line a line string
 * @return a vector of words in the line
 */
vector<string> lexer(const string& line);

#endif
