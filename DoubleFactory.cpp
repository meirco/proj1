//
// Created by meir on 24/12/18.
//

#include <iostream>
#include "DoubleFactory.h"

/**
 * the class make a string to "double" string if their is double value exist in the maps.
 */

DoubleFactory::DoubleFactory()  {}


string DoubleFactory :: convertToDouble(string str) {
    vector<string> vec;

    string check = " ";
    string afterCheck = " ";


    regex reg3("[/^(\\+|\\-|-|\\*|\\/|||||,|-|||!|||))$/]");
    int i, j=0;

    string str1;

    // removing all the ' ' from the string.
    for (int k = 0; k < str.length() ; k++) {
        if(str.at(k) != ' ') {
            str1 += str.at(k);
        }
    }

    int getValue; // the value from the map of the variable.

    for (i = 0; i < str1.length() ; i++) {
        if(regex_match(str1.substr(i, 1), reg3)) {
            check = str1.substr(j, i - j);
            if (dataBase->getStrDoubleMap().find(check) != dataBase->getStrDoubleMap().end()) {
                getValue = dataBase->getStrDoubleMap()[check];
                afterCheck += std::to_string(getValue);
                afterCheck += str1.substr(i, 1);
            }
            else if (dataBase->getStrDoubleMap().find(check) == dataBase->getStrDoubleMap().end()) {
                afterCheck += check;
                afterCheck += str1.substr(i, 1);
            }
            j = i+1;
        }
    }

    if(dataBase->getStrDoubleMap().find(str1.substr(j, i-j)) != dataBase->getStrDoubleMap().end()) {
        check = str1.substr(j, i-j);
        getValue = dataBase->getStrDoubleMap()[check];
        afterCheck += std::to_string(getValue);
    }
    else {
        afterCheck += str1.substr(j, i-j);
    }

    return afterCheck;




}
