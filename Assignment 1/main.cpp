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
    struct sockaddr_in address = initSocketAddr(AF_INET, 27015, INADDR_ANY);
    int socket1 = createSocket(AF_INET, SOCK_STREAM, 0);
    printf("main reached the end\n");
    return 0;
  }

// This function will initialize the address of the socket
sockaddr_in initSocketAddr(short family, u_short port, u_int ipAddr) {
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
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
