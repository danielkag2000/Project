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
            throw Exception("variable: " + this->var + " , not found!");
        }

        return (*got).second;
    }
};

/**
 * represent a binary Expression.
 */
class BinaryExpression : public Expression {
private:
    Expression& left;  // the first expression
    Expression& right;  // the second expression

public:
    BinaryExpression(Expression& exp1, Expression& exp2) : left(exp1), right(exp2) {}

    virtual double calculate(variables assignment) throw (Exception) = 0;

protected:
    Expression& getLeftExpresion() {
        return this->left;
    }

    Expression& getRightExpresion() {
        return this->right;
    }
};

/**
 * represent a plus Expression.
 */
class Plus : public BinaryExpression {

public:
    Plus(Expression& exp1, Expression& exp2) : BinaryExpression(exp1, exp2) {}

    virtual double calculate(variables assignment) throw (Exception) {
        return getLeftExpresion().calculate(assignment) + getRightExpresion().calculate(assignment);
    }
};

/**
 * represent a minus Expression.
 */
class Minus : public BinaryExpression {

public:
    Minus(Expression& exp1, Expression& exp2) : BinaryExpression(exp1, exp2) {}

    virtual double calculate(variables assignment) throw (Exception) {
        return getLeftExpresion().calculate(assignment) - getRightExpresion().calculate(assignment);
    }
};

/**
 * represent a division Expression.
 */
class Div : public BinaryExpression {

public:
    Div(Expression& exp1, Expression& exp2) : BinaryExpression(exp1, exp2) {}

    virtual double calculate(variables assignment) throw (Exception) {
        double rightCalc = getRightExpresion().calculate(assignment);

        if (rightCalc == 0) {
            throw Exception("Arithmetical Exception: can not divide by zero!");
        }

        return getLeftExpresion().calculate(assignment) / rightCalc;
    }
};

/**
 * represent a multiply Expression.
 */
class Mul : public BinaryExpression {

public:
    Mul(Expression& exp1, Expression& exp2) : BinaryExpression(exp1, exp2) {}

    virtual double calculate(variables assignment) throw (Exception) {
        return getLeftExpresion().calculate(assignment) * getRightExpresion().calculate(assignment);
    }
};

#endif //PROJECT_EXPRESSION_TYPES_H
