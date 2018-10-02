// Assignment 1
// Author: Bader Abdulwaseem
// UCID: 30023849
// CPSC 441

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <cstring>

using namespace std;

// Function declarations
sockaddr_in initSocketAddr(short family, u_short port, u_int ipAddr);
int createSocket(int domain, int type, int protocol);

int main(int argc, char * const argv[]) {
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address = initSocketAddr(AF_INET, 27015, INADDR_ANY); // Initializing socket address
    int listentingSocket = createSocket(AF_INET, SOCK_STREAM, 0); // Initalizing socket
    int status; // This willbe used to determine the status of the socket functions

    status = bind(listentingSocket, (struct sockaddr*)&address, sizeof(struct sockaddr_in)); // Binding socket to address
    if (status == -1) {
        printf("bind() call failed.");
        return 1;
    }

    status = listen(listentingSocket, 5);    // Listening to the socket, setting queue length of 5
    if (status == -1) {
        printf("listen() call failed.");
        return 1;
    }

    int dataSocket = accept(listentingSocket, NULL, NULL); // Attempting to accept the connection from a web browser
    if (dataSocket == -1) {
        printf("Failed to accept a connection.");
        return 1;
    }
    else {
        printf("Connection succussful!\n");
    }

    // Declaring variables to be used with the snd() and rcv() functions
    char sndMessage[4096];
    char recvMessage[4096 + 1];
    int count;

    // Going to receive data from the client
    count = recv(dataSocket, recvMessage, 4096, 0);
    recvMessage[count] = '\0'; // Null terminating the array
    printf("Data: \n%s\n", recvMessage);

    printf("main reached the end\n");
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
        printf("socket() call failed.");
        return newSocket;
    }
    return newSocket;
}
