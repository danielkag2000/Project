#ifndef PROJECT_EXP_H
#define PROJECT_EXP_H

#include <unordered_map>
#include <string>
#include "../exceptions.h"
#include "../vars/stable.h"

using namespace std;
typedef unordered_map<string, double> variables;


/**
 * Expression is a mat Mathematical Expressions
 * with arguments and sings.
 */
class Expression {
public:

    /**
     * A convenience method. Like the `evaluate(assignment)`,
     * but uses an empty assignment.
     *
     * @return the result
     * @throws Exception If the expression contains a variable
     *         which is not in the assignment, an exception
     *         is thrown.
     *
    virtual double calculate() final {
        return calculate(variables());
    }*/

    /**
     * Evaluate the expression using the variable values provided
     * in the assignment, and return the result.
     *
     * @param assignment the map
     * @return the result.
     * @throws Exception If the expression contains a variable
     *         which is not in the assignment, an exception
     *         is thrown.
     */
    virtual double calculate(SymbolTable& vars) = 0;

    virtual string returnValue(SymbolTable& vars) = 0;

    virtual ~Expression() { };
};

#endif //PROJECT_EXP_H
