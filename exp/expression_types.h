#ifndef PROJECT_EXPRESSION_TYPES_H
#define PROJECT_EXPRESSION_TYPES_H

#include "exp.h"


/**
 * represent a number Expression.
 */
class Num {
private:
    double number;

public:
    Num(double num) {
        this->number = num;
    }

    Num(const string num) {
        this->number = stod(num);
    }

    virtual double calculate(variables assignment) throw (Exception) {
        return this->number;
    }
};

/**
 * represent a variable Expression.
 */
class Var {
private:
    string var;

public:
    Var(const string variable) {
        this->var = variable;
    }

    virtual double calculate(variables assignment) throw (Exception) {
        variables::const_iterator got = assignment.find(this->var);

        if (got == assignment.end()) {
            throw VarUndefinedException(this->var);
        }

        return (*got).second;
    }
};

/**
 * represent a binary Expression.
 */
class BinaryExpression : public Expression {
private:
    Expression& _left;  // the first expression
    Expression& _right;  // the second expression

protected:
    virtual double operation(double x, double y) = 0;

public:
    BinaryExpression(Expression& exp1, Expression& exp2) : _left(exp1), _right(exp2) {}

    virtual double calculate(variables assignment) throw (Exception) final {
        return operation(_left.calculate(assignment), _right.calculate(assignment));
    }
};

/**
 * represent a plus Expression.
 */
class Plus : public BinaryExpression {

public:
    Plus(Expression& exp1, Expression& exp2) : BinaryExpression(exp1, exp2) {}

protected:
    virtual double operation(double x, double y) { return x + y; }
};

/**
 * represent a minus Expression.
 */
class Minus : public BinaryExpression {

public:
    Minus(Expression& exp1, Expression& exp2) : BinaryExpression(exp1, exp2) {}

protected:
    virtual double operation(double x, double y) {
        return x - y;
    }
};

/**
 * represent a division Expression.
 */
class Div : public BinaryExpression {

public:
    Div(Expression& exp1, Expression& exp2) : BinaryExpression(exp1, exp2) {}

protected:
    virtual double operation(double x, double y) {
        if (y == 0) {
            throw DivisionByZeroException();
        }

        return x / y;
    }
};

/**
 * represent a multiply Expression.
 */
class Mul : public BinaryExpression {

public:
    Mul(Expression& exp1, Expression& exp2) : BinaryExpression(exp1, exp2) {}

protected:
    virtual double operation(double x, double y) {
        return x * y;
    }
};

/**
 * represent a unary Expression.
 */
class UnaryExpression : public Expression {
private:
    Expression& _exp;  // the first expression

protected:
    virtual double operation(double x) = 0;

public:
    UnaryExpression(Expression& exp) : _exp(exp) {}

    virtual double calculate(variables assignment) throw (Exception) final {
        return operation(_exp.calculate(assignment));
    }
};

/**
 * represent a negative Expression.
 */
class Neg : public UnaryExpression {
public:
    Neg(Expression& exp) : UnaryExpression(exp) {}

protected:
    virtual double operation(double x) {
        return -1 * x;
    }
};

#endif //PROJECT_EXPRESSION_TYPES_H
