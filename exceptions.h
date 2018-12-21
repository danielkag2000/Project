#ifndef PROJECT_EXCEPTIONS_H
#define PROJECT_EXCEPTIONS_H

#include <iostream>
#include <string>
#include <exception>

struct Exception : public std::exception {
private:
    std::string _msg;
public:
    Exception(const std::string& msg) {
        std::cout << msg << std::endl;
        _msg = msg;
    }

    virtual const char* what() const throw() {
        return _msg.c_str();
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

struct SocketException : public Exception {
    SocketException(const std::string& msg)
        : Exception("Socket Exception: " + msg) {

    }
};

struct UnclosedSocketException : public SocketException {
    UnclosedSocketException(const std::string& msg)
            : SocketException("Socket not closed:: " + msg) {

    }
};

struct VariableAlreadyDeclaredException : public Exception {
    VariableAlreadyDeclaredException(const std::string& varname)
        : Exception("Variable already declared:: " + varname){

    }
};

#endif //PROJECT_EXCEPTIONS_H
