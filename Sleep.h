//
// Created by gil on 20/12/18.
//

#ifndef EX3_SLEEP_H
#define EX3_SLEEP_H


#include "Command.h"

class Sleep : public Command {

public:
    int execute(vector<string> vector1) override;

};


#endif //EX3_SLEEP_H
