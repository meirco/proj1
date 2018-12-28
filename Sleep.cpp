//
// Created by gil on 20/12/18.
//

#include <unistd.h>
#include <iostream>
#include "Sleep.h"
#include "ShuntingYard.h"
#include "DoubleFactory.h"

int Sleep::execute(vector<string> vector1) {

    ShuntingYard shuntingYard;
    DoubleFactory doubleFactory;



    string allSleep = " ";
    for (int i = 1; i < vector1.size() ; i++) {
        allSleep += vector1[i];
    }
    string extractFromVar = doubleFactory.convertToDouble(allSleep);
    Expression* expressionPtr = shuntingYard.evaluate(extractFromVar);
    double newValue = expressionPtr->calculate();


//    int microSeconds= stoi(vector1.at(1));
    usleep(newValue * 1000);
//    int count = vector1.size();
    return 2;
}
