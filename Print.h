//
// Created by gil on 20/12/18.
//

#ifndef EX3_PRINT_H
#define EX3_PRINT_H


#include "Command.h"

class Print : public Command {
public:
    int execute(vector<string> vector1) override;

};


#endif //EX3_PRINT_H
