#ifndef PROJECT_EXCEPTIONS_H
#define PROJECT_EXCEPTIONS_H

#include <iostream>
#include <string>

struct Exception {
    Exception(const std::string& msg) {
        std::cout << msg << std::endl;
    }
};

struct VarUndefinedException : public Exception {
    VarUndefinedException(const std::string& var) :
        Exception("Exception: variable: " + var + " , not found!") { }
};

struct ArithmeticException : public Exception {
    ArithmeticException(const std::string& msg) :
        Exception("Arithmetic Exception: " + msg) {

    }
};

struct DivisionByZeroException : public ArithmeticException {
    DivisionByZeroException() :
        ArithmeticException("can not divide by zero!") {
    }
};

#endif //PROJECT_EXCEPTIONS_H
