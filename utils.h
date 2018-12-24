//
// Created by Evyatar on 12/22/2018.
//

#ifndef PROJECT_UTILS_H
#define PROJECT_UTILS_H

#include <string>
#include <regex>

bool isNumber(const std::string& s);
bool isVariable(const std::string& s);
bool isVarNum(const std::string& s);
bool isExpr(const std::string& s);

#endif
