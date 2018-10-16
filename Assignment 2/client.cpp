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

    // Setting up the address for the client socket
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress = initSocketAddr(AF_INET, 27015, INADDR_ANY);
    int clientSocket = createSocket(AF_INET, SOCK_STREAM, 0);

    int status = connect(clientSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    if (status == -1) {
        cout << "Connection failed." << endl;
        return 1;
    }
    else {
        cout << "Connected to the server!" << endl;
    }

    // Getting input from the user
    char message[BUFFER_SIZE];
    cout << "Enter a message to the server." << endl;

    cin.getline(message, sizeof(message));

    // Sending message from the user to the server
    send(clientSocket, message, strlen(message), 0);


    close(clientSocket);

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
