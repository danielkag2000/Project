#ifndef PROJECT_EXP_H
#define PROJECT_EXP_H

#include <unordered_map>
#include <string>
#include "exceptions.h"

typedef unordered_map<string, double> variables;
using namespace std;

/**
 * Expression is a mat Mathematical Expressions
 * with arguments and sings.
 */
class expression {
public:

    /**
     * A convenience method. Like the `evaluate(assignment)`,
     * but uses an empty assignment.
     *
     * @return the result
     * @throws Exception If the expression contains a variable
     *         which is not in the assignment, an exception
     *         is thrown.
     */
    double calculate() throw {exception} final {
        return calculate(variables());
    }

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
    virtual double calculate(variables assignment) throw {exception} = 0;
};


#endif //PROJECT_EXP_H
