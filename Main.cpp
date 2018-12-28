#include <iostream>
#include <list>
#include "fstream"
#include "map"
#include "LexParser.h"
#include "Command.h"
#include "DoubleFactory.h"
#include "ShuntingYard.h"
#include "Exit.h"

using namespace std;

map<string, Command*> commandMap;
vector<string> lexeredList;

int main() {
    DataBase* dataBase = DataBase::getInstance();
//    dataBase->setDoubleForVariable("h0", 555);
//    DoubleFactory("h0/5*7773-me");
//    ShuntingYard shuntingYard("5+3");



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    string line, afterLex, conditionLines;
    // TODO tests
    ifstream myFile;
    myFile.open("./test.txt");
    if(myFile.is_open()) {
        while(!myFile.eof()) {
            getline(myFile, line);
            if (line.size() == 0)
                break;

            while(line.at(0) == ' ') {
                line.erase(0,1);
            }

            int sulsulCount = 0;
            if(line.substr(0,5) == "while" || (line.substr(0,2) == "if")) {
                sulsulCount++;
                // reading all the lines until "}".
                while(getline(myFile, conditionLines)) {
                    if(conditionLines.substr(0,5) == "while" ||(conditionLines.substr(0,2) == "if")) {
                        sulsulCount++;
                    }
                    line+= " $ "; // $ is symbol of new line.
                    line += conditionLines;
                    if(conditionLines.find('}') != string::npos) {
                        sulsulCount--;
                        if(sulsulCount == 0) {
                            break; // go out from while loop
                        }

                    }
                }
            }
            lexParser *lexer1 = new lexParser(line);
            delete lexer1;
        }
    }
    else {
        cout<< "Error opening file";
    }


//    pthread_exit(nullptr);
    Exit exit1;
    exit1.execute(lexeredList);
    return 0;
}