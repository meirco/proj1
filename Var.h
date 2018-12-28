//
// Created by gil on 20/12/18.
//

#ifndef EX3_VAR_H
#define EX3_VAR_H


#include "Command.h"

class Var : public Command {

    string bindStr = "bind";

public:
    int execute(vector<string> vector1) override;

};


#endif //EX3_VAR_H
