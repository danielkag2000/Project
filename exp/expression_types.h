#ifndef PROJECT_EXPRESSION_TYPES_H
#define PROJECT_EXPRESSION_TYPES_H

#include <exp.h>

/**
 * represent a binary Expression.
 */
class binary_expression : public expression {
private:
    expression first_expression, second_expression;  // the expressions

public:
    binary_expression(expression exp1, expression exp2) {
        this.first_expression = exp1;
        this.second_expression = exp2;
    }

    virtual double calculate(variables assignment) throw {exception} = 0;

protected:
    expression getFirstExpresion() {
        return this->first_expression;
    }

    expression getSecondExpresion() {
        return this->second_expression;
    }
};

/**
 * represent a binary Expression.
 */
class plus : public binary_expression {

public:
    plus(expression exp1, expression exp2) : first_expression(exp1), second_expression(exp2) {}

    virtual double calculate(variables assignment) throw {exception} {
        return getFirstExpresion().calculate(assignment) + getSecondExpresion().calculate(assignment);
    }
};



#endif //PROJECT_EXPRESSION_TYPES_H
