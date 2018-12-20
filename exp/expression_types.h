#ifndef PROJECT_EXPRESSION_TYPES_H
#define PROJECT_EXPRESSION_TYPES_H

#include "exp.h"


/**
 * represent a number Expression.
 */
class Num  : public Expression {
private:
    double number;

public:
    Num(double num) {
        this->number = num;
    }

    Num(const string num) {
        this->number = stod(num);
    }

    virtual double calculate(SymbolTable vars) {
        return this->number;
    }
};

/**
 * represent a variable Expression.
 */
class Var : public Expression {
private:
    string var;

public:
    Var(const string variable) {
        this->var = variable;
    }

    virtual double calculate(SymbolTable vars) {
        if (!vars.exists(this->var)) {
            throw VarUndefinedException(this->var);
        }

        return vars.get(this->var);
    }
};

/**
 * represent a binary Expression.
 */
class BinaryExpression : public Expression {
private:
    Expression* _left;  // the first expression
    Expression* _right;  // the second expression

protected:
    virtual double operation(double x, double y) = 0;

public:
    BinaryExpression(Expression* exp1, Expression* exp2) {
        this->_left = exp1;
        this->_right = exp2;
    }

    virtual double calculate(SymbolTable vars) final {
        return operation(_left->calculate(vars), _right->calculate(vars));
    }

    virtual ~BinaryExpression() {
        delete _left;
        delete _right;
    }
};

/**
 * represent a plus Expression.
 */
class Plus : public BinaryExpression {

public:
    Plus(Expression* exp1, Expression* exp2) : BinaryExpression(exp1, exp2) {}

protected:
    virtual double operation(double x, double y) { return x + y; }
};

/**
 * represent a minus Expression.
 */
class Minus : public BinaryExpression {

public:
    Minus(Expression* exp1, Expression* exp2) : BinaryExpression(exp1, exp2) {}

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
    Div(Expression* exp1, Expression* exp2) : BinaryExpression(exp1, exp2) {}

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
    Mul(Expression* exp1, Expression* exp2) : BinaryExpression(exp1, exp2) {}

protected:
    virtual double operation(double x, double y) {
        return x * y;
    }
};

/**
 * represent a boolean Expression.
 */
class BooleanExpression : public BinaryExpression {

protected:
    virtual double operation(double x, double y) = 0;

public:
    BooleanExpression(Expression* exp1, Expression* exp2) : BinaryExpression(exp1, exp2) {}
};

/**
 * represent a boolean Expression greater than.
 */
class Greater : public BooleanExpression {
public:
    Greater(Expression* exp1, Expression* exp2) : BooleanExpression(exp1, exp2) {}

protected:
    virtual double operation(double x, double y) {
        return x > y;
    }
};

/**
 * represent a boolean Expression less than.
 */
class Less : public BooleanExpression {
public:
    Less(Expression* exp1, Expression* exp2) : BooleanExpression(exp1, exp2) {}

protected:
    virtual double operation(double x, double y) {
        return x < y;
    }
};

/**
 * represent a boolean Expression greater equal.
 */
class GreaterEqual : public BooleanExpression {
public:
    GreaterEqual(Expression* exp1, Expression* exp2) : BooleanExpression(exp1, exp2) {}

protected:
    virtual double operation(double x, double y) {
        return x >= y;
    }
};

/**
 * represent a boolean Expression less equal.
 */
class LessEqual : public BooleanExpression {
public:
    LessEqual(Expression* exp1, Expression* exp2) : BooleanExpression(exp1, exp2) {}

protected:
    virtual double operation(double x, double y) {
        return x <= y;
    }
};

/**
 * represent a boolean Expression equal to.
 */
class Equal : public BooleanExpression {
public:
    Equal(Expression* exp1, Expression* exp2) : BooleanExpression(exp1, exp2) {}

protected:
    virtual double operation(double x, double y) {
        return x == y;
    }
};

/**
 * represent a boolean Expression not equal to.
 */
class NotEqual : public BooleanExpression {
public:
    NotEqual(Expression* exp1, Expression* exp2) : BooleanExpression(exp1, exp2) {}

protected:
    virtual double operation(double x, double y) {
        return x != y;
    }
};

#endif //PROJECT_EXPRESSION_TYPES_H
