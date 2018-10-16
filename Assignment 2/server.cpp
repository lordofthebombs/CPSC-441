/*  Author: Bader Abdulwaseem
    UCID: 30023849
    Assignment 2
*/

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <cstdio>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 140

using namespace std;

// Function declarations
sockaddr_in initSocketAddr(short family, u_short port, u_int ipAddr);
int createSocket(int domain, int type, int protocol);

int main(int argc, char * const argv[]) {

    // Setting up the address for the server socket
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress = initSocketAddr(AF_INET, 27015, INADDR_ANY);
    int listeningSocket = createSocket(AF_INET, SOCK_STREAM, 0);

    int status; // This willbe used to determine the status of the socket functions
    status = bind(listeningSocket, (struct sockaddr*)&serverAddress, sizeof(struct sockaddr_in)); // Binding socket to address
    if (status == -1) {
        cout << "bind() call failed." << endl;
        return 1;
    }

    status = listen(listeningSocket, 5);    // Listening to the socket, setting queue length of 5
    if (status == -1) {
        cout << "listen() call failed." << endl;
        return 1;
    }

    int dataSocket = accept(listeningSocket, NULL, NULL);
    if (dataSocket == -1) {
        cout << "accept() call failed";
    }
    else {
        cout << "Connection accepted!" << endl;
    }

    char cMessage[BUFFER_SIZE];
    string message;

    int byteCount = recv(dataSocket, cMessage, BUFFER_SIZE, 0);

    // Adding null terminator because I guess cin.getLine() doesn't include it
    cMessage[byteCount + 1] = '\0'

    // Converting char array to string to make parsing "easier"
    message = string(cMessage);
    cout << message << endl;

    close(dataSocket);
    close(listeningSocket);

    return 0;
}

// This function will initialize the address of the socket
sockaddr_in initSocketAddr(short family, u_short port, u_int ipAddr) {
    struct sockaddr_in address;
    address.sin_family = family;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(ipAddr);
    return address;
}

// This function will take a arguments on which type of socket is being created
int createSocket(int domain, int type, int protocol) {
    int newSocket = socket(domain, type, protocol);
    if (newSocket == -1) {
        cout << "socket() call failed." << endl;
        return newSocket;
    }
    return newSocket;
}
