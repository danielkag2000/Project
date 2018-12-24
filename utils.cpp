#include "utils.h"

std::regex numRegex("-?\\d+(\\.\\d+)?");
std::regex varRegex("[a-zA-Z_][a-zA-Z_0-9]*");

bool isNumber(const std::string& s) {
    return regex_match(s, numRegex);
}

bool isVariable(const std::string& s) {
    return regex_match(s, varRegex);
}

bool isVarNum(const std::string& s) {
    return isNumber(s) || isVariable(s);
}

bool isExpr(const std::string& s) {
    return isVarNum(s) || s == ")";
}