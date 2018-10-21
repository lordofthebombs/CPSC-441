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
#include <sstream>

#define BUFFER_SIZE 140

using namespace std;

// Function declarations
sockaddr_in initSocketAddr(short family, u_short port, u_int ipAddr);
int createSocket(int domain, int type, int protocol);
vector<string> stringSplit(string str, char delim);
map<int, string> sequentialIndex(map<int, string>, vector<string> words);
string seqDecode(string index, map<int, string> m);
string seqEncode(map<int, string> m);

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

    // Declaring the maps to be used in the encryptions

    map<int, string> seqMap;
    map<int, string> sumMap;
    map<int, string> otherMap;

    // Infinitely looping, receiving messages from client
    while (1) {
        int byteCount = recv(dataSocket, cMessage, BUFFER_SIZE, 0);

        // Converting char array to string to make parsing "easier"
        message = string(cMessage);
        cout << message << endl;

        // Splitting the string into individual words
        vector<string> words = stringSplit(message, ' ');

        seqMap = sequentialIndex(seqMap, words);

        // If the message starts with a 0, we can assume the client is sending
        // an encoded message and wants to decode it. The encoded words are
        // Simply going to be stored in the words vector and shouldn't affect
        // anything else in the program.
        if (cMessage[0] == '0') {
            message = "";
            for (int i = 0; i < words.size(); i++) {
                message += seqDecode(words[i], seqMap) + " ";
            }
        }
        strcpy(cMessage, message.c_str());
        byteCount = send(dataSocket, cMessage, sizeof(cMessage) + 1, 0);
    }



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

// Function taken from conrjac from GitHub.com
// Modifed slightly by me
// https://gist.github.com/conrjac/5387376
vector<string> stringSplit(string str, char delim) {
	istringstream ss(str);
	string token;
	vector<string> words;

	while(getline(ss, token, delim)) {
		words.push_back(token);
	}

    return words;
}

// This function takes in a map and a vector of strings as input, and maps each
// string into its own place sequentially
map<int, string> sequentialIndex(map<int, string> m, vector<string> words) {
    for (int i = m.size(); i < words.size(); i++) {
        m[i] = words[i];
    }
    return m;
}

// Returns string mapped at index. It does this by stripping the 0x off of the
// number and gives it just a number
string seqDecode(string index, map<int, string> m) {
    int i = stoi(index.substr(2, index.size()));
    return m[i];
}

// Encodes each string with its index
string seqEncode(map<int, string> m) {
    return "";
}
