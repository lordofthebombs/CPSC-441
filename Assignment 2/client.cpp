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
    char clientMessage[BUFFER_SIZE];
    char serverMessage[BUFFER_SIZE];
    char userInput[BUFFER_SIZE];
    string message;
    cout << "Choose which encoding scheme you want." << endl;
    cout << "(1) Sequential\n(2) Wordsum\n(3) Bader's encryption\nOr, press (4) to exit." << endl;

    // There will be 4 choices to choose from, each that will cause a different
    // encryption method or to close the client. Currently all the options do
    // the same thing.

    int choice;
    while (1) {
        cin.getline(userInput, sizeof(userInput));
        choice = stoi(userInput);

        if (choice == 1) {
            cout << "\nEnter the message you wish to encode/decode." << endl;
            cin.getline(clientMessage, sizeof(clientMessage));
            send(clientSocket, clientMessage, strlen(clientMessage) + 1, 0);
        }

        else if (choice == 2) {
            cout << "\nEnter the message you wish to encode/decode." << endl;
            cin.getline(clientMessage, sizeof(clientMessage));
            send(clientSocket, clientMessage, strlen(clientMessage) + 1, 0);
        }

        else if (choice == 3) {
            cout << "\nEnter the message you wish to encode/decode." << endl;
            cin.getline(clientMessage, sizeof(clientMessage));
            send(clientSocket, clientMessage, strlen(clientMessage) + 1, 0);
        }

        else if (choice == 4) {
            break;
        }

        else {
            cout << "Please enter a valid option!" << endl;
        }

        // Receiving encoded message from the server
        int byteCount = recv(clientSocket, serverMessage, BUFFER_SIZE, 0);

        message = string(serverMessage);
        cout << message << endl;
    }

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
