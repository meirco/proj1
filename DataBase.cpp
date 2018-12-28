//
// Created by meir on 22/12/18.
//

#include "DataBase.h"

using namespace std;


DataBase* DataBase :: instance = nullptr;


DataBase::DataBase() {}


DataBase *DataBase::getInstance() {
    if(!instance) {
        instance = new DataBase;
    }
    return instance;
}

DataBase::~DataBase() {
    delete instance; /////
}


// set one variable with its path.
void DataBase:: setStringsForPath(string variable, string path) {
    this->varPath[variable] = path;

}
// set one variable with its value.
void DataBase:: setDoubleForVariable(string variable, double value) {
    this->strDoubleMap[variable] = value;
}

void DataBase::setXmlMap(string variable, double value) {
    this->xmlMap[variable] =value;
}

// the map getters.
 map<string, string> &DataBase::getVarPath()  {
    return varPath;
}

 map<string, double> &DataBase::getStrDoubleMap()  {
    return strDoubleMap;
}

map<string, double >& DataBase::getXmlMap() {
    return xmlMap;
}
/*
instrumentation/airspeed-indicator/indicated-speed-kt
instrumentation/altimeter/indicated-altitude-ft
instrumentation/altimeter/indicated-altitude-ft
instrumentation/attitude-indicator/indicated-pitch-deg
instrumentation/attitude-indicator/indicated-roll-deg
instrumentation/attitude-indicator/internal-pitch-deg
instrumentation/attitude-indicator/internal-roll-deg
instrumentation/encoder/indicated-altitude-ft
instrumentation/encoder/pressure-alt-ft
instrumentation/gps/indicated-altitude-ft
instrumentation/gps/indicated-ground-speed-kt
instrumentation/gps/indicated-vertical-speed
instrumentation/heading-indicator/indicated-heading-deg
instrumentation/magnetic-compass/indicated-heading-deg
instrumentation/slip-skid-ball/indicated-slip-skid
instrumentation/turn-indicator/indicated-turn-rate
instrumentation/vertical-speed-indicator/indicated-speed-fpm
controls/flight/aileron
controls/flight/elevator
controls/flight/rudder
controls/flight/flaps
controls/engines/engine/throttle
engines/engine/rpm
 * */
void DataBase::initializeXmlMap(){

    xmlMap.insert(pair<string, double >("instrumentation/airspeed-indicator/indicated-speed-kt", 0));
    xmlMap.insert(pair<string, double >("instrumentation/altimeter/indicated-altitude-ft", 0));
    xmlMap.insert(pair<string, double >("instrumentation/altimeter/indicated-altitude-ft", 0));
    xmlMap.insert(pair<string, double >("instrumentation/attitude-indicator/indicated-pitch-deg", 0));
    xmlMap.insert(pair<string, double >("instrumentation/attitude-indicator/indicated-roll-deg", 0));
    xmlMap.insert(pair<string, double >("instrumentation/attitude-indicator/internal-pitch-deg", 0));
    xmlMap.insert(pair<string, double >("instrumentation/attitude-indicator/internal-roll-deg", 0));
    xmlMap.insert(pair<string, double >("instrumentation/encoder/indicated-altitude-ft", 0));
    xmlMap.insert(pair<string, double >("instrumentation/encoder/pressure-alt-ft", 0));
    xmlMap.insert(pair<string, double >("instrumentation/gps/indicated-altitude-ft", 0));
    xmlMap.insert(pair<string, double >("instrumentation/gps/indicated-ground-speed-kt", 0));
    xmlMap.insert(pair<string, double >("instrumentation/gps/indicated-vertical-speed", 0));
    xmlMap.insert(pair<string, double >("instrumentation/heading-indicator/indicated-heading-deg", 0));
    xmlMap.insert(pair<string, double >("instrumentation/magnetic-compass/indicated-heading-deg", 0));
    xmlMap.insert(pair<string, double >("instrumentation/slip-skid-ball/indicated-slip-skid", 0));
    xmlMap.insert(pair<string, double >("instrumentation/turn-indicator/indicated-turn-rate", 0));
    xmlMap.insert(pair<string, double >("instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0));
    xmlMap.insert(pair<string, double >("controls/flight/aileron", 0));
    xmlMap.insert(pair<string, double >("controls/flight/elevator", 0));
    xmlMap.insert(pair<string, double >("controls/flight/rudder", 0));
    xmlMap.insert(pair<string, double >("controls/flight/flaps", 0));
    xmlMap.insert(pair<string, double >("controls/engines/engine/throttle", 0));
    xmlMap.insert(pair<string, double >("engines/engine/rpm", 0));

}

void DataBase:: initializeXmlPath() {
    xmlPath.push_back("instrumentation/airspeed-indicator/indicated-speed-kt");
    xmlPath.push_back("instrumentation/altimeter/indicated-altitude-ft");
    xmlPath.push_back("instrumentation/altimeter/indicated-altitude-ft");
    xmlPath.push_back("instrumentation/attitude-indicator/indicated-pitch-deg");
    xmlPath.push_back("instrumentation/attitude-indicator/indicated-roll-deg");
    xmlPath.push_back("instrumentation/attitude-indicator/internal-pitch-deg");
    xmlPath.push_back("instrumentation/attitude-indicator/internal-roll-deg");
    xmlPath.push_back("instrumentation/encoder/indicated-altitude-ft");
    xmlPath.push_back("instrumentation/encoder/pressure-alt-ft");
    xmlPath.push_back("instrumentation/gps/indicated-altitude-ft");
    xmlPath.push_back("instrumentation/gps/indicated-ground-speed-kt");
    xmlPath.push_back("instrumentation/gps/indicated-vertical-speed");
    xmlPath.push_back("instrumentation/heading-indicator/indicated-heading-deg");
    xmlPath.push_back("instrumentation/magnetic-compass/indicated-heading-deg");
    xmlPath.push_back("instrumentation/slip-skid-ball/indicated-slip-skid");
    xmlPath.push_back("instrumentation/turn-indicator/indicated-turn-rate");
    xmlPath.push_back("instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    xmlPath.push_back("controls/flight/aileron");
    xmlPath.push_back("controls/flight/elevator");
    xmlPath.push_back("controls/flight/rudder");
    xmlPath.push_back("controls/flight/flaps");
    xmlPath.push_back("controls/engines/engine/throttle");
    xmlPath.push_back("engines/engine/rpm");

}

bool DataBase::isOpenCloseFlag(){
    return openCloseFlag; //first implementation will be at the start of OpenDataServer command.
}

void DataBase::setOpenCloseFlag(bool openCloseFlag) {
    DataBase::openCloseFlag = openCloseFlag;
}

int DataBase::getGlobalClientSockFd()  {
    return globalClientSockFd;
}

void DataBase::setGlobalClientSockFd(int globalClientSockFd) {
    DataBase::globalClientSockFd = globalClientSockFd;
}


//void DataBase::initializeXmlDouble()  {
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//    xmlPath.push_back(0);
//}










