//
// Created by gil on 18/12/18.
//

#ifndef EX3_COMMAND_H
#define EX3_COMMAND_H

#include <list>
#include <string>
#include <vector>

using namespace std;

class Command {
public:
    virtual int execute(vector<string> vector1) =0;
};

//openDataServer
//connect
//var
//bind there is a note at the targil instructions page 5 at the end.
// =
//while
//if
//print
//sleep
//exit

// git clone https://github.com/meirco/ex3.git

#endif //EX3_COMMAND_H