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
    address = initSocketAddr(AF_INET, 27015, INADDR_ANY);
    int socket1 = createSocket(AF_INET, SOCK_STREAM, 0);
    int status;
    status = bind(socket1, (struct sockaddr*)&address, sizeof(struct sockaddr_in)); // Binding socket to address

    if (status == -1) {
        printf("bind() call failed.");
    }

    status = listen(socket1, 5);    // Listening to the socket, setting queue length of 5
    if (status == -1) {
        printf("listen() call failed.");
    }

    status = connect(socket1, (struct sockaddr*)&address, sizeof(struct sockaddr_in));  // Connecting socket to the server(?)
    if (status == -1) {
        printf("connect() call failed.\n");
    }

    printf("before accept\n");
    int socket2 = accept(socket1, NULL, NULL);  // Accepting the connection from socket1(?)
    if (socket2 == -1) {
        printf("accept() call failed.");
    }
    printf("after accept\n");

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
