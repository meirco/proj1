//
// Created by gil on 20/12/18.
//

#ifndef EX3_CONNECT_H
#define EX3_CONNECT_H


#include "Command.h"

class Connect : public Command {
public:
    int execute(vector<string> vector1) override;
//    static void* ConnectClient(void* args);
    void enterChar();

};


#endif //EX3_CONNECT_H
