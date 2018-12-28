//
// Created by meir on 24/12/18.
//

#ifndef EX3_DOUBLEFACTORY_H
#define EX3_DOUBLEFACTORY_H

#include <string>
#include <regex>
#include "DataBase.h"

using namespace std;

class DoubleFactory {
public:
    DoubleFactory();

    string convertToDouble(string str);

    DataBase* dataBase = DataBase:: getInstance();


private:

    string str;


};


#endif //EX3_DOUBLEFACTORY_H
