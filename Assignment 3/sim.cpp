#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>


#define BUFFER_SIZE 100
#define START 0.0

using namespace std;

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



struct qosData {
    double delay = 0.0;
    int packetsLost = 0;
    double packetLoss;
} data;

int main(int argc, char * argv[]) {
    // Simulating a buffer by representing it as the amount of elements a it has
    vector<int> queue;

    double arrivalTime = START;
    // Delay = arrival time of current packet - previous packet's transmission time
    double delayTime = 0.0;
    // Transmission time = packet size / transmission speed
    double transmisionTime START;
    double transmissionSpeed = 11000000.0;
    int packetSize;
    long int packets = 0;

    // Each line will be split into two pairs of
    vector<string> pair;
    ifstream inputFile;
    inputFile.open("soccersmall.txt");

    string line;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            packet++;   // Incrementing to count total number of packets
            pair = stringSplit(line, " ");
            arrivalTime = stod(pair[0]);
            packetSize = stoi(pair[1]) * 8; // Multiplying by 8 to count the number of bits

            /*
                Add these ideas later:
                If arrivalTime < transmisionTime
                push size of packet to the queue
                if queue is full, i.e. queue size is BUFFER_SIZE, drop the packet
                when the current packet is done transmitting, continue with the next one
            */
    }

    else {
        cerr << "File failed to open." << endl;
    }

    inputFile.close();

    return 0;
}
