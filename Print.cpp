//
// Created by gil on 20/12/18.
//

#include <iostream>
#include "Print.h"
#include "DoubleFactory.h"
#include "ShuntingYard.h"

using namespace std;

int Print::execute(vector<string> vector1) {

    ShuntingYard shuntingYard;
    DoubleFactory doubleFactory;
    bool w = false;
    string allStr = " ";
    string marks = "\"";


// check if we need to print " " or not
    for (int i = 1; i < vector1.size() ; i++) {
        if(vector1[i].find(marks) != std::string::npos) {
            w = true;
            break;
        }
    }

    // making the string.
    for (int i = 1; i < vector1.size(); ++i) {
        allStr += vector1[i];
    }

    // if w is a pure string
    if(w) {
        cout << allStr<< endl; // TODO erase the ".
    }
    else if(w == false) {

        string extractFromVar = doubleFactory.convertToDouble(allStr);
        Expression* expressionPtr = shuntingYard.evaluate(extractFromVar);
        double newValue = expressionPtr->calculate();
        cout << newValue<< endl;
    }

    return 1;

}
