//
// Created by gil on 20/12/18.
//

#ifndef EX3_WHILE_H
#define EX3_WHILE_H


#include "Command.h"
#include "LexParser.h"
#include "ConditionParser.h"


class While : public Command {

protected:
    ConditionParser* cond;

public:
    While(ConditionParser*);

    int execute(vector<string> vector1);

};


#endif //EX3_WHILE_H
