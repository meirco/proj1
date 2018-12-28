//
// Created by Gil on 18/12/18.
//

#include <map>
#include "Expression.h"
#include "stack"

using namespace std;

#ifndef UNTITLED8_SHUNTINGYARD_H
#define UNTITLED8_SHUNTINGYARD_H

class ShuntingYard {
    map<char, int> precedences;
    string inputString;

public:
//    ShuntingYard(string inputString);

    ShuntingYard();


    void initializeMap();

    int precedence(char operation);

    virtual Expression* evaluate(string tokens);

    Expression* applyOp(Expression* left, Expression*  right, char operation);

    int test();

    int checkNeg(string token);


};

#endif //EX3_SHUNTINGYARDALGO_H
