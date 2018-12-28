//
// Created by gil on 20/12/18.
//

#ifndef EX3_IF_H
#define EX3_IF_H


#include "While.h"

class If : public While {
public:
    If(ConditionParser*);

    int execute(vector<string> vector1) override;

};


#endif //EX3_IF_H
