#ifndef PROJECT_EXPRESSION_MAP_H
#define PROJECT_EXPRESSION_MAP_H

#include <unordered_map>
#include "exp.h"
#include "expression_types.h"
#include "../command/command_expression.h"

class MapExpression {
private:
    unordered_map<string, Expression*> _expressions;

public:
    MapExpression() {
        this->_expressions = unordered_map<string, Expression*>();
    }

    ~MapExpression() {
        for(unordered_map<string, Expression*>::iterator it = _expressions.begin(); it != _expressions.end(); ++it) {
            delete it->second;
        }
    }

    void add(string key, Expression* val) {
        _expressions.insert(pair<string, Expression*>(key, val));
    }

    Expression* get(string key) {
        if(_expressions.find(key) != _expressions.end()){
            return _expressions.find(key)->second;
        }
        return nullptr;
    }
};

#endif //PROJECT_EXPRESSION_MAP_H
