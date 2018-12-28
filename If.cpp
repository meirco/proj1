//
// Created by gil on 20/12/18.
//

#include "If.h"

If::If(ConditionParser* _cond): While(_cond) {}

int If::execute(vector<string> vector1) {
    lexParser parser;
    if(cond->toContinue()) {
        for (int i = 1; i < cond->commandsVec.size(); i++) {
            Command* c = cond->commandsVec[i];
            c->execute(parser.start(cond->commandLineVector[i]));
        }
    }

    return 0;
}
