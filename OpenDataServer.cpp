//
// Created by gil on 19/12/18.
//

//close the socket.

#include <stdlib.h>
#include <unistd.h>
#include <memory.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <mutex>
#include <thread>
#include "OpenDataServer.h"
#define NUM_OF_ARGS 23

//using namespace std;


struct Args{
    int numOfTimesToReadDataPerSecond;
    int newsockfd;
};
bool serverIsConnected;

void* ConnectServer(void* args) {
    int n;
    mutex mtx;
    char buffer[1000], buffer2[1000];
    struct Args *args1 = (struct Args *) args;
    DataBase *dataBase = DataBase::getInstance();

    while (dataBase->isOpenCloseFlag()) { //Global flag = true;

        mtx.lock(); //critic code = we don't want that something will change the maps while we there.

        bzero(buffer, 1000);
        n = read(args1->newsockfd, buffer, 999); //read line from simulator to socket.
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }
        serverIsConnected = true;

        strcpy(buffer2 ,buffer); //backup for buffer.
        //cout << "Buffer " <<  buffer << endl;

        /* now we take the buffer, saperate to tokens and insert them to vector*/
        vector<double> lineArguments;
        char* copyString;
        copyString=strtok(buffer, ","); //from the net whole while loop
        while (copyString != NULL) {
            lineArguments.push_back(stod(copyString)); //insert current token to vector
            copyString = strtok(NULL, ","); //Yani i++ next token
        }
        //cout << "lineArguments " <<  lineArguments.size() << endl;

        for (int i = 0; i < NUM_OF_ARGS; ++i) { //max args = 23



            switch (i) {
                case 0:
                    dataBase->setXmlMap("instrumentation/airspeed-indicator/indicated-speed-kt", lineArguments.at(0));
                    break;
                case 1:
                    dataBase->setXmlMap("instrumentation/altimeter/indicated-altitude-ft",lineArguments.at(1));
                    break;
                case 2:
                    dataBase->setXmlMap("instrumentation/altimeter/indicated-altitude-ft",lineArguments.at(2));
                    break;
                case 3:
                    dataBase->setXmlMap("instrumentation/attitude-indicator/indicated-pitch-deg",lineArguments.at(3));
                    break;
                case 4:
                    dataBase->setXmlMap("instrumentation/attitude-indicator/indicated-roll-deg", lineArguments.at(4));
                    break;
                case 5:
                    dataBase->setXmlMap("instrumentation/attitude-indicator/internal-pitch-deg", lineArguments.at(5));
                    break;
                case 6:
                    dataBase->setXmlMap("instrumentation/attitude-indicator/internal-roll-deg", lineArguments.at(6));
                    break;
                case 7:
                    dataBase->setXmlMap("instrumentation/encoder/indicated-altitude-ft", lineArguments.at(7));
                    break;
                case 8:
                    dataBase->setXmlMap("instrumentation/encoder/pressure-alt-ft", lineArguments.at(8));
                    break;
                case 9:
                    dataBase->setXmlMap("instrumentation/gps/indicated-altitude-ft", lineArguments.at(9));
                    break;
                case 10:
                    dataBase->setXmlMap("instrumentation/gps/indicated-ground-speed-kt", lineArguments.at(10));
                    break;
                case 11:
                    dataBase->setXmlMap("instrumentation/gps/indicated-vertical-speed", lineArguments.at(11));
                    break;
                case 12:
                    dataBase->setXmlMap("instrumentation/heading-indicator/indicated-heading-deg", lineArguments.at(12));
                    break;
                case 13:
                    dataBase->setXmlMap("instrumentation/magnetic-compass/indicated-heading-deg", lineArguments.at(13));
                    break;
                case 14:
                    dataBase->setXmlMap("instrumentation/slip-skid-ball/indicated-slip-skid", lineArguments.at(14));
                    break;
                case 15:
                    dataBase->setXmlMap("instrumentation/turn-indicator/indicated-turn-rate", lineArguments.at(15));
                    break;
                case 16:
                    dataBase->setXmlMap("instrumentation/vertical-speed-indicator/indicated-speed-fpm", lineArguments.at(16));
                    break;
                case 17:
                    dataBase->setXmlMap("controls/flight/aileron", lineArguments.at(17));
                    break;
                case 18:
                    dataBase->setXmlMap("controls/flight/elevator", lineArguments.at(18));
                    break;
                case 19:
                    dataBase->setXmlMap("controls/flight/rudder", lineArguments.at(19));
                    break;
                case 20:
                    dataBase->setXmlMap("controls/flight/flaps", lineArguments.at(20));
                    break;
                case 21:
                    dataBase->setXmlMap("controls/engines/engine/throttle",  lineArguments.at(21));
                    break;
                case 22:
                    dataBase->setXmlMap("engines/engine/rpm", lineArguments.at(22));
                    break;
                default:
                    break;
            }
        }
//        //check what we have in the XmlMap:
        for(auto it = dataBase->getXmlMap().cbegin(); it != dataBase->getXmlMap().cend(); ++it)
        {
            cout <<it->first<< it->second<<endl;
        }


//        printf("Here is the message: %s\n", buffer2); //print the whole line from the simulator.

        /* Write a response to the client */
        n = write(args1->newsockfd, "I got your message", 18);

        if (n < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }

        mtx.unlock(); //finish critic code = unlock mtx.

        usleep((1 / (args1->numOfTimesToReadDataPerSecond))*1000); // number of times to read the XML each second.
    }

    /*Release all sources*/
//    close(args1->newsockfd);
    delete (args1);
    return nullptr;
}

int OpenDataServer::execute(vector<string> vector1) {
    int sockfd, newsockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    serverIsConnected = false;

    DataBase *dataBase1 = DataBase::getInstance();
    dataBase1->setOpenCloseFlag(true); //flag that will be true until the process will end.

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = stoi(vector1[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    cout << "try to connect" << endl;
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, (socklen_t*)&clilen);
    cout << "Connected" << endl;
    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    struct Args* args1 = new Args();
//    args1->portNumber = stoi(vector1[1]);
    args1->numOfTimesToReadDataPerSecond=stoi(vector1[2]);
    args1->newsockfd = newsockfd;
//    thread serverThread(ConnectServer, args1);
//    serverThread.detach();
    pthread_t trid; //Declare the thread.
    pthread_create(&trid, nullptr, ConnectServer, args1);

//    close(sockfd);
//        pthread_join(trid, nullptr);
//    delete(args1);
    return vector1.size(); //num of elements to move the index at the parser's list.
}