#ifndef PROJECT_EXCEPTIONS_H
#define PROJECT_EXCEPTIONS_H

#include <iostream>
#include <string>
#include <exception>

struct Exception : public std::exception {
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

struct SyntaxException : public Exception {
    SyntaxException(const std::string& msg) :
        Exception("Syntax Exception: " + msg) {

    }
};

struct InvalidParenthesisOrder : public SyntaxException {
    InvalidParenthesisOrder() :
        SyntaxException("Invalid parenthesis order inserted!") {

    }
};

#endif //PROJECT_EXCEPTIONS_H
