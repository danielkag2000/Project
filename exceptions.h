#ifndef PROJECT_EXCEPTIONS_H
#define PROJECT_EXCEPTIONS_H

#include <iostream>
#include <string>

struct exception {
    exception(const std::string& msg) {
        std::cout << msg << std::endl;
    }
};

#endif //PROJECT_EXCEPTIONS_H
