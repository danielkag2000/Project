#include "lexer.h"

#include <algorithm>
#include <set>


set<char> breaks{ ',', ' ' };

vector<string> lexer(const string& line) {
    vector<string> words;

    auto curr = line.begin();
    do {
        // find a separator character (or end of line)
        auto separator = find_if(curr, line.end(), [](char c) {
            return breaks.count(c) > 0;
        });

        // if the word read is not an empty word
        if (curr < separator) {
            // push word according to position of separator
            words.push_back(string(curr, separator));
        }

        // finish on end of line
        if (separator == line.end()) {
            break;
        }

        // move to next word
        curr = separator + 1;
    } while (true);

    return words;
}