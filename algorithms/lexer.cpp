#include <regex>
#include <iostream>
#include <list>
#include "lexer.h"
#include "../exceptions.h"
#include "../utils.h"

/*
 * variables    [a-zA-Z_][a-zA-Z_0-9]*
 *  strings     ".*"
 *  literals    (\d+(\.\d+)*)
 *  keywords    [a-zA-Z_][a-zA-Z_0-9]*
 *  symbols     \+|-|\*|\/|==|=|<=|<|>=|>|\(|\)|{|}|!=
 *
 *  total:      ([a-zA-Z_][a-zA-Z_0-9]*)|(\".*\")|(((?<=\s)\-)?\d+(\.\d+)*)|(\+|\-|\*|\/|\=\=|\=|\<\=|\<|\>\=|\>|\(|\)|\{|\})|( |,)
 */

#define KEYVARS     1
#define STRINGS     2
#define LITERALS    3
#define SYMBOLS     5
#define WHITESPACE  6
#define COMMA       7

/**
 * Get a regex for identifying types
 * @return a regex
 */
regex getIdentifierRegex() {
    string regex_separator =
            "([a-zA-Z_][a-zA-Z_0-9]*)"      // variables & keywords
            "|(\".*\")"                     // strings
            "|(\\d+(\\.\\d+)*)"             // literals
            // symbols
            "|(\\+|\\-|\\*|\\/|\\=\\=|\\=|\\<\\=|\\<|\\>\\=|\\>|\\(|\\)|\\{|\\}|\\!\\=)"

            "|(\\s+)"                       // whitespaces
            "|([,]+)"                       // commas
    ;

    return regex(regex_separator);
}

/**
 * Checks if a flagged int is of a given group
 * @param flags the flagged int
 * @param groupID the group id
 * @return true if it is, false otherwise
 */
inline bool isGroup(int flags, int groupID) {
    return (bool) (flags & (1 << groupID));
}

regex separator(getIdentifierRegex());

/**
 * Checks if a regex matched a given group
 * @param match the regex match object
 * @param groupId the group id
 * @return true if it matched, false otherwise
 */
inline bool groupMatched(smatch& match, int groupId) {
    return match[groupId].matched;
}

list<int> possibilities{ KEYVARS, STRINGS, LITERALS, SYMBOLS, WHITESPACE, COMMA };

/**
 * Sets the flags for a given int according to a given match
 * @param x the int
 * @param m the match
 */
void setFlags(int& x, smatch& m) {
    for (int possibility : possibilities) {
        if (groupMatched(m, possibility)) {
            x = 1 << possibility;
            return;
        }
    }

    x = 0;
}

// all combinations that are not allowed after each other
list<pair<int, int>> notAllowed{
//        { SYMBOLS, SYMBOLS },

        { LITERALS, STRINGS }, { LITERALS, KEYVARS },
        { STRINGS, LITERALS }, { STRINGS, KEYVARS },
        { KEYVARS, LITERALS }, { KEYVARS, STRINGS }
};

/**
 * Ensures the legality of a previous match before the current match
 * @param prev the previous flagged match
 * @param curr the current match
 * @return true if legal, false otherwise
 */
bool isLegal(int prev, int curr) {
    for (auto& bad : notAllowed) {
        if (isGroup(prev, bad.first) && isGroup(curr, bad.second)) {
            // if matched a bad match
            return false;
        }
    }

    return true;
}

inline void badStringException(const string& line) {
    throw SyntaxException("Invalid string entered: " + line);
}

inline bool canHaveMinus(int flags) {
    return isGroup(flags, LITERALS) || isGroup(flags, KEYVARS);
}

/**
 * Checks whether the current word should be minus united with a previous minus(if exists)
 * It makes sure that the minus should be inserted and that it doesn't belong to other expression
 * @param words a list of the previous words(to check if it includes a minus)
 * @param curr the current match flag
 * @return true if should unite, false otherwise
 */
inline bool shouldUniteMinus(vector<string>& words, int curr) {
    return !words.empty() && words.back() == "-" && canHaveMinus(curr)
           && (words.size() <= 1 || (words.end()[-2]) == "," || (words.end()[-2]) == "=");
}

inline bool shouldUniteBind(vector<string>& words) {
    return !words.empty() && words.back() == "=";
}

vector<string> uniteThings(vector<string>& v);

vector<string> lexer(const string &line) {
    vector<string> words;
    auto phrases_begin = sregex_iterator(line.begin(), line.end(), separator);
    auto phrases_end = sregex_iterator();

    int prev = 0, curr;
    int nextBegin = (*phrases_begin).position(0);

    vector<int> previousMatches;

    for (auto i = phrases_begin; i != phrases_end; ++i) {
        // for using previous flags
        prev = previousMatches.empty() ? 0 : previousMatches.back();

        smatch match = *i;

        // initialize match string values
        string str(match.str());
        int pos = match.position(0);
        int endpos = pos + str.length();

        // if skipped a character in the iteration, it must have been illegal
        if (pos != nextBegin) badStringException(line);

        // check for legality in order of words
        setFlags(curr, match);
        if (!isLegal(prev, curr)) badStringException(line);

        // if had a minus before and current is a literal
        if (shouldUniteMinus(words, curr))
            // unite the literal with the minus
            words.back() += str;
            // turn every = bind to =bind
        else if (str == "bind" && shouldUniteBind(words))
            words.back() += str;
            // if we should push the current string as a word
        else if (!str.empty()
                 && !isGroup(curr, WHITESPACE))
            words.push_back(str);

        // prepare for next iteration
        nextBegin = endpos;
        previousMatches.push_back(curr);
    }

    return uniteThings(words);
}

vector<string> uniteThings(vector<string>& v) {
    if (v.empty())
        return v;

    vector<string> united{v[0]};

    for (unsigned int i = 1; i < v.size(); i++) {
        if ( (v[i] == "bind" && v[i - 1] == "=")
            || (v[i] == "-" && !isExpr(v[i - 1]))) {
            /*
             * unite every = bind to =bind
             * unite every - expr to -expr
             */
            // unite every = bind to =bind
            united.front() += v[i];
        }
        else {
            united.push_back(v[i]);
        }
    }

    return united;
}