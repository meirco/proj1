//
// Created by gil on 20/12/18.
//

#include <iostream>
#include <sys/socket.h>
#include "Equal.h"
#include "DataBase.h"
#include "ShuntingYard.h"
#include "DoubleFactory.h"


//} else {
//EvaluateExp *evaluateExp1= new EvaluateExp(ve[2], this->glob);
//string eval1 = evaluateExp1->Infix_To_Prefix(ve[2]);
//Expression *x = evaluateExp1->evaluatePrefix(eval1);
//double value = x->calculate(ve);
//string path;
//path+="set ";
//string addr=glob->OPgetVarBindTbl(ve[0]);
//path+=addr;
//string strValue = to_string(value);
//path+=strValue;
//path+="\r\n";
//sendMessage(path);
////  pthread_mutex_lock(&mutexIns);
////this->glob->setIns(path);
////  pthread_mutex_unlock(&mutexIns);
////  pthread_mutex_lock(&mutexXml);
//this->glob->inserSymbTbl(ve[0],value);
////   pthread_mutex_unlock(&mutexXml);
//}
//}
//

void Equal::sendMessage(string path) {
    DataBase *dataBase1 = DataBase::getInstance();
    char *s = const_cast<char *>(path.c_str());
//    /* Send message to the server */
    int sockfd = dataBase1->getGlobalClientSockFd();// number of socket id
    int n;
    if (::send(sockfd, path.data(), strlen(path.data()), 0) < 0) {
        perror("ERROR writing to socket");
        exit(1);
    };
    cout << "Path: " << path.data() << endl;
    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
}


int Equal::execute(vector<string> vector1) {

    int flag = 0;

    // vector iterator
    vector<string>::iterator it;

    DataBase *dataBase = DataBase::getInstance();

    ShuntingYard shuntingYard;

    DoubleFactory doubleFactory;

    string left = " ";
    string right = " ";

    // checking where is the '=' sign
    for (it = vector1.begin(); it != vector1.end(); it++) {
        if (*it == "=") {
            break;
        }
    }
    long equalIndex = it - vector1.begin(); // the '=' index.

    /**
     * arrange the string , the right and the left.
     */
    for (int i = 0; i < equalIndex; i++) {
        left += vector1[i];
//        left += " ";
    }

    for (int j = equalIndex + 1; j < vector1.size(); j++) {
        right += vector1[j];
//            right += " ";
    }

    // making the right string 'double' string

    string strDoubleVar = doubleFactory.convertToDouble(right);

    if (strDoubleVar.at(0) == ' ') {
        if (strDoubleVar.at(1) == '-') {
            strDoubleVar.replace(strDoubleVar.find(' '), 1, "0");
        }
    }


    Expression *expression = shuntingYard.evaluate(strDoubleVar);
    double valueNew = expression->calculate();
    string var = vector1[0];

    dataBase->setDoubleForVariable(var, valueNew);

    delete expression;

    /*Send massage to socket*/

    string varPath = dataBase->getVarPath().at(var);
    string path;
    path = "set " + varPath + " " + to_string(valueNew) + "\r\n";
    sendMessage(path);////////////

    return valueNew; // maybe not needed.TODO check it.
}
