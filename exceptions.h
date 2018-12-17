#ifndef PROJECT_EXCEPTIONS_H
#define PROJECT_EXCEPTIONS_H

#include <iostream>

struct Exception {
    Exception(const string& msg) {
        std::cout << msg << std::endl;
    }
};

#endif //PROJECT_EXCEPTIONS_H
