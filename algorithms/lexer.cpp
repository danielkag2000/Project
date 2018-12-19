#include "lexer.h"
#include <regex>
#include <iostream>

/*
 * variables    [a-zA-Z_][a-zA-Z_0-9]*
 *  strings     \".*\"
 *  literals    (((?<=\s)\-)?\d+(\.\d+)*)
 *  keywords    [a-zA-Z_][a-zA-Z_0-9]*
 *  symbols     \+|\-|\*|\/|\=\=|\=|\<\=|\<|\>\=|\>|\(|\)|\{|\}
 *
 *  total:      ([a-zA-Z_][a-zA-Z_0-9]*)|(\".*\")|(((?<=\s)\-)?\d+(\.\d+)*)|(\+|\-|\*|\/|\=\=|\=|\<\=|\<|\>\=|\>|\(|\)|\{|\})|( |,)
 */

#define KEYVARS     0
#define STRINGS     1
#define LITERALS    2
#define SYMBOLS     3
#define WHITESPACE  8

string regex_separator =
        "|([a-zA-Z_][a-zA-Z_0-9]*)"                 // variables & keywords
        "|(\\\".*\\\")"                             // strings
        "|(\\d+(\\.\\d+)*)"                         // literals
        // symbols
        "|(\\+|\\-|\\*|\\/|\\=\\=|\\=|\\<\\=|\\<|\\>\\=|\\>|\\(|\\)|\\{|\\})"

        "|([ ,]+)"                                    // whitespaces
        ;

// (, x, +, 3, ), *, -, 4,

// (x +3)*-4
// x 3 + * 4 -

// x 3 + 4 - *
// (x +3)*(-4)

// (xy8_2+3.14159)*689*(pi+boy_123)
// xy8_2 3.14159 + 689 pi boy_123 + * *

regex separator(regex_separator);

inline bool groupMatched(smatch& match, int groupId) {
    return !match[groupId].str().empty();
}

struct previousMatch {
    bool whitespace;
    bool string;
    bool var;
    bool literal;
    bool symbol;
};

void resetPrev(previousMatch& pm) {
    pm.whitespace = false;
    pm.string = false;
    pm.var = false;
    pm.literal = false;
    pm.symbol = false;
}

bool legalMatch(previousMatch& prev, smatch& match) {
    if (groupMatched(match, WHITESPACE)) {
        resetPrev(prev);
        prev.whitespace = true;
        return true;
    }

    bool isVar      = groupMatched(match, KEYVARS);
    bool isLiteral  = groupMatched(match, LITERALS);
    bool isString   = groupMatched(match, STRINGS);
    bool isSymbol   = groupMatched(match, SYMBOLS);

    if (!prev.whitespace) {
        if (prev.literal && groupMatched(match, KEYVARS)) {
            // cannot allow literals right before vars
            return false;
        }

        prev.whitespace = false;

    }


    prev.whitespace = false;
    return true;
}

vector<string> lexer(const string &line) {
    vector<string> words;
    auto phrases_begin = sregex_iterator(line.begin(), line.end(), separator);
    auto phrases_end = sregex_iterator();

    bool prev_whitespace = false;
    for (auto i = phrases_begin; i != phrases_end; ++i) {
        smatch match = *i;

        if (groupMatched(match, WHITESPACE)) {
            prev_whitespace = true;
            continue;
        } else {
            prev_whitespace = false;
        }

        words.push_back(match.str());
    }

    return words;
}


//vector<string> lexer(const string& line) {
//    vector<string> words;
//
//    auto curr = line.begin();
//    do {
//        // find a separator character (or end of line)
//        auto separator = find_if(curr, line.end(), [](char c) {
//            return breaks.count(c) > 0;
//        });
//
//        // if the word read is not an empty word
//        if (curr < separator) {
//            // push word according to position of separator
//            words.push_back(string(curr, separator));
//        }
//
//        // finish on end of line
//        if (separator == line.end()) {
//            break;
//        }
//
//        // move to next word
//        curr = separator + 1;
//    } while (true);
//
//    return separateWords(words, ops);
//}
