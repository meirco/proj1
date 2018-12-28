//
// Created by meir on 24/12/18.
//

#include "ConditionParser.h"
#include "While.h"
#include "If.h"
#include "DoubleFactory.h"
#include "ShuntingYard.h"
#include <algorithm>
#include <regex>
#include "Condition.h"
#include "Print.h"
#include "Var.h"
#include "Sleep.h"
#include "Bind.h"
#include "Exit.h"
#include "Connect.h"
#include "OpenDataServer.h"
#include "Equal.h"

using namespace std;

ConditionParser::ConditionParser()
{
    leftExp = NULL;
    rightExp = NULL;

}

ConditionParser::~ConditionParser()
{
    delete leftExp;
    delete rightExp;

}

string remove_ws(const string& str)
{
    string str_no_ws;
    for (char c: str)
        if (! std::isspace(c))
            str_no_ws += c;
    return str_no_ws;
}

int ConditionParser::execute(vector<string> vector1) {

    DataBase* dataBase = DataBase::getInstance();

    vector<string> firstWord;
    // the first command in the commands vector.


    firstWord.push_back(vector1[0]); // the first command 'while' or 'if'.
    int i, k = 0;
    string wholeCommand = " ";
    for (i = 0; i < vector1.size(); i++) {
        wholeCommand += vector1[i];
        wholeCommand += " ";
        if (vector1[i].find("$") != string::npos) { // $ is the sign '\n' - end line.
            commandLineVector.push_back(wholeCommand); // inserting into the vector the command line.
            k++;
            wholeCommand = " "; // erasing the string before filling it more time.
            // taking the word command.
            if(!((vector1[i+1].find("}")!= string::npos) || (vector1[i+1].find("}")!= string::npos))) {
                  firstWord.push_back(vector1[i+1]);
            }
        }
    }



    // cleaning the strings.
    for (int j = 0; j < commandLineVector.size(); j++) {
        commandLineVector[j].erase(std::remove(commandLineVector[j].begin(), commandLineVector[j].end(), '$'),
                                   commandLineVector[j].end());
    }
    for (int j = 0; j < commandLineVector.size(); j++) {
        commandLineVector[j].erase(std::remove(commandLineVector[j].begin(), commandLineVector[j].end(), '{'),
                                   commandLineVector[j].end());
    }



    for (int z = 0; z < firstWord.size() ; z++) {

        if(firstWord[z].find("while") != string::npos) {
            commandsVec.push_back((Command*)new While( this));
        }
        else if(firstWord[z].find("if") != string::npos) {
            commandsVec.push_back((Command*)new If(this));
        }
        else if(firstWord[z].find("print") != string::npos) {
            commandsVec.push_back((Command*)new Print());
        }
        else if(firstWord[z].find("var") != string::npos) {
            commandsVec.push_back((Command*)new Var());
        }
        else if(firstWord[z].find("bind") != string::npos) {
            commandsVec.push_back((Command*)new Bind());
        }
        else if(firstWord[z].find("connect") != string::npos) {
            commandsVec.push_back((Command*)new Connect());
        }
        else if(firstWord[z].find("openDataServer") != string::npos) {
            commandsVec.push_back((Command*)new OpenDataServer());
        }
        else if(firstWord[z].find("exit") != string::npos) {
            commandsVec.push_back((Command*)new Exit());
        }
        else if(firstWord[z].find("sleep") != string::npos) {
            commandsVec.push_back((Command*)new Sleep());
        }
        else if(dataBase->getStrDoubleMap().find(firstWord[z]) != dataBase->getStrDoubleMap().end()) { // the variables
            commandsVec.push_back((Command*)new Equal());
        }

    }


    /**
     * now we have vector with all the commands.
     */


    string oper = " ";


    regex reg4("[/^(||}|{|>|<|>=|<=|==||&|\\||%|!|\\^|\\(|\\))$/]");
    int j;
    string left;
    string right;
    string finalCondition = " ";
    int position = 0;
    if ((commandLineVector[0].find("while") !=string::npos) || (commandLineVector[0].find("if") != string::npos)) {

        // if we found "while" or "if" we want to check where is the condition sign.
        for (j = 0; j < commandLineVector[0].size(); ++j) {
            if (regex_match(commandLineVector[0].substr(j, 2), reg4)) {
                oper = commandLineVector[0].substr(j, 2);
                break;
            }
            else if(regex_match(commandLineVector[0].substr(j,1), reg4)) {
                oper = commandLineVector[0].substr(j, 1);
                break;
            }
        }
        position = j; // the condition sign position. we found the condition sign index


        if(regex_match(commandLineVector[0].substr(position+1,1), reg4)) { //their is 2 operators.
            oper = commandLineVector[0].substr(position, 2);
            position++;

            for (int m = 0; m < position - 1; m++) {
                left += commandLineVector[0].at(m);
            }

            if(commandLineVector[0].find("while")!= string::npos) { // if the word is while.
                left.erase(0, 6); // erasing the 'while', we have the left exp.
            }
            else if(commandLineVector[0].find("if") != string:: npos){
                left.erase(0, 3); // erasing the 'while', we have the left exp.
            }


            for (int n = position + 1; n < commandLineVector[0].size(); n++) {
                right += commandLineVector[0].at(n);// we have the right exp.
            }
        }

        else { // when we have one operator
            for (int m = 0; m < position; m++) {
                left += commandLineVector[0].at(m);
            }

            if(commandLineVector[0].find("while") != std::string::npos) { // if the word is while.
                left.erase(0, 6); // erasing the 'while', we have the left exp.
            }
            else if(commandLineVector[0].find("if") != std::string::npos){
                left.erase(0, 3); // erasing the 'while', we have the left exp.
            }


            for (int n = position + 1; n < commandLineVector[0].size(); n++) {
                right += commandLineVector[0].at(n);// we have the right exp.
            }
        }
    }


    ShuntingYard shuntingYard;
    DoubleFactory doubleFactory;

    string leftStr = doubleFactory.convertToDouble(left); // check if the left is a variable
    string rightStr = doubleFactory.convertToDouble(right);

//    left = remove_ws(left);////////
//    right = remove_ws(right);
    leftExp = new VariableExpression(left);
    rightExp = new VariableExpression(right);

    if(rightStr.at(0) == ' ') { // check if right value has '-' before.
        if(rightStr.at(1) == '-') {
            rightStr.replace(rightStr.find(' '), 1, "0");
        }
    }
    Expression* expressionPtr = shuntingYard.evaluate(rightStr);
    this->rightValue = expressionPtr->calculate(); // now we had the values of the condition, left and right.

    Expression* expression = shuntingYard.evaluate(leftStr);
    this->leftValue = expression->calculate();
    conditionOper = oper;


    if (commandLineVector.at(0).find("while") !=std::string::npos ) {
        While *w = new While(this);
        w->execute(commandLineVector);
        delete w;
    } else if (commandLineMap.begin()->second.find("if") == string::npos) {
        If *ifCommand = new If(this);
        ifCommand->execute(commandLineVector);
        delete ifCommand;

    }
}

bool ConditionParser:: toContinue() {

    double leftValue = leftExp->calculate();
    double rightValue = rightExp->calculate();
    CompareCondition* condition = nullptr;
    bool isTrue= false;

    if(conditionOper.find("<") != string::npos) {  // this->commandLineVector[0][position]
        condition = new OperatorSmall((leftValue), (rightValue));
        if(condition->evaluate()) {
            isTrue = true;
        }


    } else if(conditionOper.find(">") != string::npos) {
            condition = new OperatorBig((leftValue), (rightValue));
            if(condition->evaluate()) {
                isTrue = true;
            }
        }
        else if(conditionOper.find(">=") != string::npos) {
            condition = new OperatorBigEqual((leftValue), (rightValue));
            if(condition->evaluate()) {
                isTrue = true;
            }
        }

        else if(conditionOper.find("<=") != string::npos) {
            condition = new OperatorSmallEqual((leftValue), (rightValue));
            if(condition->evaluate()) {
                isTrue = true;
            }
        }

        else if(conditionOper.find("!=") != string::npos) {
            condition = new OperatorNotEqual((leftValue), (rightValue));
            if(condition->evaluate()) {
                isTrue = true;
            }
        }

        else if(conditionOper.find("==") != string::npos) {
            condition = new OperatorEquals((leftValue), (rightValue));
            if(condition->evaluate()) {
                isTrue = true;
            }
        }
        delete condition;
    return isTrue;
    }



    // getters.
 vector<Command *> &ConditionParser::getCommandsVec()  {
    return commandsVec;
}

double ConditionParser::getLeftValue()  {
    return leftValue;
}

double ConditionParser::getRightValue()  {
    return rightValue;
}

const string &ConditionParser::getConditionOper()  {
    return conditionOper;
}


