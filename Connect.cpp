//
// Created by gil on 20/12/18.
//
#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string.h>
#include <unistd.h>
#include <strings.h>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <iostream>
#include <thread>
#include <mutex>
#include "Connect.h"
#include "DataBase.h"

extern bool serverIsConnected;

using namespace std;

//void Connect::enterChar() {
//    cout<< "Press enter after opening Simulator" << endl;
//    cin.ignore();
//}

//struct Args{
//    int sockfd;
//};
//
//void* ConnectClient(void* args){
//    int  n;
////    mutex mtx;
//    char buffer[1000];
//    struct Args *args1 = (struct Args*) args;
//    int sockfd = args1->sockfd;
//
//
//    cout<<"connection happend" << endl;
//    while(true) {
//
//        mtx.lock();
//
//        /* Now ask for a message from the user, this message
//       * will be read by server
//    */
//        printf("Please enter the message: ");
//        bzero(buffer,1000);
//        fgets(buffer,999,stdin);
//
//        /* Send message to the server */
//        n = write(sockfd, buffer, strlen(buffer));
//
//        if (n < 0) {
//            perror("ERROR writing to socket");
//            exit(1);
//        }
//
//        /* Now read server response */
//        bzero(buffer,1000);
//        n = read(sockfd, buffer, 999);
//
//        if (n < 0) {
//            perror("ERROR reading from socket");
//            exit(1);
//        }
//
//        printf("%s\n",buffer);
//
//        mtx.unlock();
//
//    }
//
//
//    delete(args1);
//    return nullptr;
//
//}

//OPen
int Connect::execute(vector<string> vector1) {
    DataBase *dataBase = DataBase::getInstance();
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    string hostIp;

    char buffer[1000];

    for (int i = 1; i < vector1.size() - 1; ++i) {
        hostIp += vector1[i];
    }
    cout << hostIp << endl;

    if (vector1.size() < 9) {
        perror("not enough arguments");
        exit(0);
    }

    portno = stoi(vector1[8]);


    if (vector1.size() < 9) {
        perror("ERROR opening socket");
        exit(0);
    }

    portno = stoi(vector1[8]);

    while (serverIsConnected == false) {

    }

    /* Create a socket point */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname(hostIp.c_str());
    cout << "Creating a client's socket" << endl;

    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    /* Now connect to the server */
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    /* Now ask for a message from the user, this message
       * will be read by server
    */
//
//        printf("Please enter the message: ");
//        bzero(buffer,256);
//        fgets(buffer,255,stdin);
//
//        /* Send message to the server */
//        n = write(sockfd, buffer, strlen(buffer));
//
//        if (n < 0) {
//            perror("ERROR writing to socket");
//            exit(1);
//        }

//        /* Now read server response */
//        bzero(buffer,256);
//        n = read(sockfd, buffer, 255);
//
//        if (n < 0) {
//            perror("ERROR reading from socket");
//            exit(1);
//        }
    dataBase->setGlobalClientSockFd(sockfd); //the Client's socket will save its fd in DATABASE.
    return 0;

}
//    int sockfd, portno, n;
//    extern bool serverIsConnected;
//    struct sockaddr_in serv_addr;
//    struct hostent *server;
//    string hostIp;
//    for (int i = 1; i <vector1.size()-1 ; ++i) {
//        hostIp+= vector1[i];
//    }
//    cout<< hostIp<<endl;
//
////    enterChar();
//
//    char buffer[1000];
//
//    if (vector1.size() < 9) {
//        perror("not enough arguments");
//        exit(0);
//    }
//
//    portno = stoi(vector1[8]);
//
//    while (serverIsConnected == false){
//
//    }
//
//    /* Create a socket point */
//    sockfd = socket(AF_INET, SOCK_STREAM, 0);
//
//    if (sockfd < 0) {
//        perror("ERROR opening socket");
//        exit(1);
//    }
//
//    server = gethostbyname(hostIp.c_str());
//    cout<<"Creating a client's socket"<<endl;
//    if (server == NULL) {
//        fprintf(stderr,"ERROR, no such host\n");
//        exit(0);
//    }
//
//    bzero((char *) &serv_addr, sizeof(serv_addr));
//    serv_addr.sin_family = AF_INET;
//    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
//    serv_addr.sin_port = htons(portno);
//
//    /* Now connect to the server */
//    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
//        perror("ERROR connecting");
//        exit(1);
//    }
//
////    cout<< "Now try to make Client's thread"  << endl;
////    struct Args* args1 = new Args();
////    args1->sockfd = sockfd;
////    pthread_t trid; //Declare the thread.
////    pthread_create(&trid, nullptr, ConnectClient, args1);
//
////    close(sockfd);
//    //    pthread_join(trid, nullptr);
////    delete(args1);
////    return vector1.size(); //num of elements to move the index at the parser's list.
////    thread clientThred(ConnectClient,args1);
////    clientThred.detach();
//
//    /* Now ask for a message from the user, this message
//       * will be read by server
//    */
//    printf("Please enter the message: ");
//    bzero(buffer,1000);
//    fgets(buffer,999,stdin);
//
//    /* Send message to the server */
//    n = write(sockfd, buffer, strlen(buffer));
//
//    if (n < 0) {
//        perror("ERROR writing to socket");
//        exit(1);
//    }
//
//    /* Now read server response */
//    bzero(buffer,1000);
//    n = read(sockfd, buffer, 999);
//
//    if (n < 0) {
//        perror("ERROR reading from socket");
//        exit(1);
//    }
//
//    printf("%s\n",buffer);
////    return 0;
//
//
//}