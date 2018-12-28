//
// Created by gil on 20/12/18.
//

#include "While.h"
#include "DataBase.h"
#include "Print.h"
#include <algorithm>

int While::execute(vector<string> vector1) {
    lexParser parser;
    while(cond->toContinue()) {
        for (int i = 1; i < cond->commandsVec.size(); i++) {
            Command* c = cond->commandsVec[i];
            c->execute(parser.start(cond->commandLineVector[i]));// making a ready vector to execute.
        }
    }

    return 0;
}

While::While(ConditionParser* c) {
    cond = c;
}
