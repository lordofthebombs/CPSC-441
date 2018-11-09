// Author: Bader Abdulwaseem
// UCID: 30023849
// Assignment 3
// Compilation instructions:

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <cstdio>

// Defining macros for constants
#define BUFFER_SIZE_DEFAULT 100
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
		double averageDelay;
};

int main(int argc, char * argv[]) {
    // This queue will contain the arrival times of the packets and their sizes
    queue<vector<double>> buffer;
	int bufferSize = BUFFER_SIZE_DEFAULT;
	qosData qos;
    // double arrivalTime = START;
    // Delay = arrival time of current packet - previous packet's transmission time
    double delayTime = 0.0;
    // Transmission time = packet size / transmission speed
    double departureTime = START;
	double currentTime = START;
	// The transmission speed is in MBps, just so I dont have to multiple the
	// packet size by 8 everytime
    double transmissionSpeed = 1375000.0;
    // double packetSize;
    long int packets = 0;

    // Each line will be split into a pair, where pair[0] is the arrival time
	// and pair[1] is the packet size
    vector<string> pairStr;
	// pairDouble will be pushed into the queue
	vector<double> pairDouble;
    ifstream inputFile;
    inputFile.open("soccer.txt");

	int pushCount = 0;
    string line;
    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            packets++;   // Incrementing to count total number of packets
            pairStr = stringSplit(line, ' ');
			pairDouble.push_back(stod(pairStr[0]));
			pairDouble.push_back(stod(pairStr[1]));


			// If a packet arrives before the current one is finished transmitting
			// add it to the queue
			if (pairDouble[0] < currentTime) {
				buffer.push(pairDouble);
				delayTime = currentTime - pairDouble[0];
			}

			if (buffer.size() == bufferSize) {
				// Drop packet
				qos.packetsLost++;
			}

			else if (buffer.size() == 0) {
				buffer.push(pairDouble);
				delayTime = 0.0;
				departureTime = buffer.front()[1] / transmissionSpeed;
				currentTime += departureTime;
				buffer.pop();
			}

			else if (buffer.size() > 0 || buffer.size() < 100) {
				buffer.push(pairDouble);
				departureTime = (buffer.front()[1] / transmissionSpeed) + delayTime;
				currentTime += departureTime;
				qos.delay += delayTime;
				buffer.pop();
			}

			// Clearing the pair
			pairDouble.pop_back();
			pairDouble.pop_back();
		}
    }

    else {
        cerr << "File failed to open." << endl;
    }

    inputFile.close();

	qos.packetLoss = (double)qos.packetsLost / (double)packets * 100.0;
	qos.averageDelay = qos.delay / packets;
	cout << "Packet loss: " << qos.packetLoss << "%" << endl;
	cout << "Average delay: " << qos.averageDelay << endl;
	cout << pushCount << endl;
    return 0;
}
