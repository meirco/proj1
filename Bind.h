//
// Created by gil on 20/12/18.
//

#ifndef EX3_BIND_H
#define EX3_BIND_H


#include "Command.h"

class Bind : public Command {
public:
    int execute(vector<string> vector1) override;

};


#endif //EX3_BIND_H
