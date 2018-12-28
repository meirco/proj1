//
// Created by meir on 24/12/18.
//

#ifndef EX3_CONDITIONPARSER_H
#define EX3_CONDITIONPARSER_H


#include <map>
#include "Command.h"

class VariableExpression;

class ConditionParser : public Command {

    VariableExpression* leftExp;
    VariableExpression* rightExp;
    double leftValue;
    double rightValue;
    string conditionOper;
public:

     vector<Command*> commandsVec;

    map<int, string> commandLineMap;

    vector<string> commandLineVector;

    enum Conditions{};

    ConditionParser();
    ~ConditionParser();

    int execute(vector<string> vector1) override;

    bool toContinue();


     vector<Command *> &getCommandsVec() ;

    double getLeftValue() ;

    double getRightValue() ;

    const string &getConditionOper() ;

};


#endif //EX3_CONDITIONPARSER_H
