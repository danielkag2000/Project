#include "utils.h"

std::regex numRegex("-?\\d+(\\.\\d+)?");

bool isNumber(const std::string& s) {
    return regex_match(s, numRegex);
}