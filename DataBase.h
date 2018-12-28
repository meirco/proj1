//
// Created by meir on 22/12/18.
//

#ifndef EX3_DATABASE_H
#define EX3_DATABASE_H

#include <map>
#include <vector>

using namespace std;


class DataBase {

private:

    map<string, string>varPath;

    map<string, double>strDoubleMap;

    map<string,double > xmlMap;

    bool openCloseFlag; //to open the client only after the server connected.

    int globalClientSockFd;




public:
    DataBase();

    static DataBase *instance;

    static DataBase *getInstance();

    vector<string> xmlPath;

    vector<double> xmlDoubles;

    void setStringsForPath(string variable, string path);

    void setDoubleForVariable(string variable, double value);

    void setXmlMap(string variable, double value);

    void initializeXmlMap();

    void initializeXmlPath();

    void initializeXmlDouble();

    map<string, string> &getVarPath() ;

     map<string, double> &getStrDoubleMap() ;

    map<string, double > &getXmlMap();


     vector<string> getXmlPath() ;

     vector<double> getXmlDoubles() ;

    void setXmlPath( vector<string> &xmlPath);

    void setXmlDoubles( vector<double> &xmlDoubles);

    bool isOpenCloseFlag();

    void setOpenCloseFlag(bool openCloseFlag);

    int getGlobalClientSockFd() ;

    void setGlobalClientSockFd(int globalClientSockFd);

    virtual ~DataBase();

};


#endif //EX3_DATABASE_H
