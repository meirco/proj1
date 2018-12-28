//
// Created by gil on 19/12/18.
//

#ifndef EX3_OPENDATASERVER_H
#define EX3_OPENDATASERVER_H



#include "Command.h"
#include "DataBase.h"

using namespace std;

class OpenDataServer: public Command {


public:
    vector<string> xmlPath;

    vector<double> xmlDoubles;

    int execute(vector<string> vector1);

    DataBase* dataBase = DataBase::getInstance();
//    DataBase* dataBase = dataBase->getInstance();

    void initializeXmlPath();

};


#endif //EX3_OPENDATASERVER_H
