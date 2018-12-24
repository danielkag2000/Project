#include "command_creator.h"
#include "../exp/expression_types.h"
#include "../exp/command_expression.h"
#include "../command/complicate_commands.h"
#include "../command/server_command.h"
#include "../command/simple_commands.h"
#include "../algorithms/shunting_yard_algorithm.h"

Expression* base_expression(SymbolTable& var_table, const string& op);

Expression* PlusCreator::create(vector<string> parameters) {
    return new Plus(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));
}

Expression* MinusCreator::create(vector<string> parameters) {
    return new Minus(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));
}


Expression* MulCreator::create(vector<string> parameters) {
    return new Mul(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));
}


Expression* DivCreator::create(vector<string> parameters) {
    return new Div(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));
}


Expression* EquCreator::create(vector<string> parameters) {
    return new Equal(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));
}


Expression* NotEquCreator::create(vector<string> parameters) {
    return new NotEqual(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));
}

Expression* GreatCreator::create(vector<string> parameters) {
    return new Greater(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));
}


Expression* LessCreator::create(vector<string> parameters) {
    return new Less(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));
}


Expression* GreatEquCreator::create(vector<string> parameters) {
    return new GreaterEqual(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));
}


Expression* LessEquCreator::create(vector<string> parameters) {
    return new LessEqual(base_expression(var_table, parameters[0]), base_expression(var_table, parameters[1]));
}


Expression* VarCreator::create(vector<string> parameters) {
    return new CommandExpression(new VarCommand(parameters[0]));
}


Expression* BindCreator::create(vector<string> parameters) {
    return new CommandExpression(new BindCommand(parameters[0], parameters[1]));
}


Expression* AssignCreator::create(vector<string> parameters) {
    Expression* exp = base_expression(var_table, parameters[1]);
    Expression* result = new CommandExpression(new AssignCommand(parameters[0], exp->calculate(var_table)));
    delete exp;
    return result;
}

Expression* PrintCreator::create(vector<string> parameters) {
    return new CommandExpression(new PrintCommand(parameters[0]));
}

Expression* SleepCreator::create(vector<string> parameters) {
    Expression* exp = base_expression(var_table, parameters[0]);
    Expression* result = new CommandExpression(new SleepCommand((int)exp->calculate(var_table)));
    delete exp;
    return result;
}

Expression* ODSCreator::create(vector<string> parameters) {
    Expression* exp1 = base_expression(var_table, parameters[0]);
    Expression* exp2 = base_expression(var_table, parameters[1]);
    Expression* result = new CommandExpression(new OpenDataServerCommand((int)exp2->calculate(var_table),
                                                                         (int)exp1->calculate(var_table)));
    delete exp1;
    delete exp2;
    return result;
}

Expression* ConnectCreator::create(vector<string> parameters) {
    Expression* exp = base_expression(var_table, parameters[1]);
    Expression* result = new CommandExpression(new ConnectCommand(parameters[0], (int)exp->calculate(var_table)));
    delete exp;
    return result;
}


Expression* WhileCreator::create(vector<string> parameters) {
    vector<string> bool_exp = run_shunting_yard(op_table, lexer(parameters[0]));
    vector<string> commands;

    for (int i = 1; i < parameters.size(); i++) {
        commands.push_back(parameters[i]);
    }
    return new CommandExpression(new LoopCommand(bool_exp, commands, op_table, cost));
}


Expression* IfCreator::create(vector<string> parameters) {
    vector<string> bool_exp = run_shunting_yard(op_table, lexer(parameters[0]));
    vector<string> commands;

    for (int i = 1; i < parameters.size(); i++) {
        commands.push_back(parameters[i]);
    }

    return new CommandExpression(new IfCommand(bool_exp, commands, op_table, cost));
}