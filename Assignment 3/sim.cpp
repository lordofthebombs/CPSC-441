// Author: Bader Abdulwaseem
// UCID: 30023849
// Assignment 3
// Compilation instructions: g++ sim.cpp -o sim.out

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
	int maxBufferSize = BUFFER_SIZE_DEFAULT;
	qosData qos11Mbps, qos6Mbps, qos54Mbps, qos30Mbps;
    // double arrivalTime = START;
    // Delay = arrival time of current packet - previous packet's transmission time
    double delayTime = 0.0;
    // Transmission time = packet size / transmission speed
    double departureTime = START;
	double currentTime = START;
	double previousPacketTime = START;
	// The transmission speed is in Bps, just so I dont have to multiple the
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
				delayTime = currentTime - pairDouble[0];
				qos11Mbps.delay += delayTime;
			}

			// When the buffer is full, it drops the packet and icrements the
			// dropped packets counter
			if (buffer.size() == maxBufferSize) {
				// Drop packet
				qos11Mbps.packetsLost++;
			}

			// When the buffer's size is 0, there will be no queuing delay as
			// it is being transmitted immediately
			else if (buffer.size() == 0) {
				buffer.push(pairDouble);
				delayTime = 0.0;
				departureTime = buffer.front()[1] / transmissionSpeed;
				currentTime += departureTime;
				buffer.pop();
			}

			// This case checks to see if the buffer is occupied by packets
			// and applies a queuing delay when the packet is finally transmitted
			else if (buffer.size() > 0 || buffer.size() < 100) {
				buffer.push(pairDouble);
				departureTime = (buffer.front()[1] / transmissionSpeed) + delayTime;
				currentTime += departureTime;
				buffer.pop();
			}

			// Clearing the pair
			pairDouble.pop_back();
			pairDouble.pop_back();
		}
    }

    else {
        cerr << "File failed to open." << endl;
		return -1;
    }

    inputFile.close();

	qos11Mbps.packetLoss = ((double)qos11Mbps.packetsLost / (double)packets) * 100.0;
	qos11Mbps.averageDelay = qos11Mbps.delay / (double)packets;

	// 6 Mbps in bytes per second
	transmissionSpeed = 750000.0;
	inputFile.open("soccer.txt");
	packets = 0;
	currentTime = START;

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            packets++;   // Incrementing to count total number of packets
            pairStr = stringSplit(line, ' ');
			pairDouble.push_back(stod(pairStr[0]));
			pairDouble.push_back(stod(pairStr[1]));

			// If a packet arrives before the current one is finished transmitting
			// add it to the queue
			if (pairDouble[0] < currentTime) {
				delayTime = currentTime - pairDouble[0];
				qos6Mbps.delay += delayTime;
			}

			// When the buffer is full, it drops the packet and icrements the
			// dropped packets counter
			if (buffer.size() == maxBufferSize) {
				// Drop packet
				qos6Mbps.packetsLost++;
			}

			// When the buffer's size is 0, there will be no queuing delay as
			// it is being transmitted immediately
			else if (buffer.size() == 0) {
				buffer.push(pairDouble);
				delayTime = 0.0;
				departureTime = buffer.front()[1] / transmissionSpeed;
				currentTime += departureTime;
				buffer.pop();
			}

			// This case checks to see if the buffer is occupied by packets
			// and applies a queuing delay when the packet is finally transmitted
			else if (buffer.size() > 0 || buffer.size() < 100) {
				buffer.push(pairDouble);
				departureTime = (buffer.front()[1] / transmissionSpeed) + delayTime;
				currentTime += departureTime;
				buffer.pop();
			}

			// Clearing the pair
			pairDouble.pop_back();
			pairDouble.pop_back();
		}
    }

    else {
        cerr << "File failed to open." << endl;
		return -1;
    }

    inputFile.close();

	qos6Mbps.packetLoss = ((double)qos6Mbps.packetsLost / (double)packets) * 100.0;
	qos6Mbps.averageDelay = qos6Mbps.delay / (double)packets;


	transmissionSpeed = 6750000.0;
	packets = 0;
	currentTime = START;
	inputFile.open("soccer.txt");

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            packets++;   // Incrementing to count total number of packets
            pairStr = stringSplit(line, ' ');
			pairDouble.push_back(stod(pairStr[0]));
			pairDouble.push_back(stod(pairStr[1]));

			// If a packet arrives before the current one is finished transmitting
			// add it to the queue
			if (pairDouble[0] < currentTime) {
				delayTime = currentTime - pairDouble[0];
				qos54Mbps.delay += delayTime;
			}

			// When the buffer is full, it drops the packet and icrements the
			// dropped packets counter
			if (buffer.size() == maxBufferSize) {
				// Drop packet
				qos54Mbps.packetsLost++;
			}

			// When the buffer's size is 0, there will be no queuing delay as
			// it is being transmitted immediately
			else if (buffer.size() == 0) {
				buffer.push(pairDouble);
				delayTime = 0.0;
				departureTime = buffer.front()[1] / transmissionSpeed;
				currentTime += departureTime;
				buffer.pop();
			}

			// This case checks to see if the buffer is occupied by packets
			// and applies a queuing delay when the packet is finally transmitted
			else if (buffer.size() > 0 || buffer.size() < 100) {
				buffer.push(pairDouble);
				departureTime = (buffer.front()[1] / transmissionSpeed) + delayTime;
				currentTime += departureTime;
				buffer.pop();
			}

			// Clearing the pair
			pairDouble.pop_back();
			pairDouble.pop_back();
		}
    }

    else {
        cerr << "File failed to open." << endl;
		return -1;
    }

    inputFile.close();

	qos54Mbps.packetLoss = ((double)qos54Mbps.packetsLost / (double)packets) * 100.0;
	qos54Mbps.averageDelay = qos54Mbps.delay / (double)packets;


	transmissionSpeed = 3750000.0;
	packets = 0;
	currentTime = START;
	inputFile.open("soccer.txt");

    if (inputFile.is_open()) {
        while (getline(inputFile, line)) {
            packets++;   // Incrementing to count total number of packets
            pairStr = stringSplit(line, ' ');
			pairDouble.push_back(stod(pairStr[0]));
			pairDouble.push_back(stod(pairStr[1]));

			// If a packet arrives before the current one is finished transmitting
			// add it to the queue
			if (pairDouble[0] < currentTime) {
				delayTime = currentTime - pairDouble[0];
				qos30Mbps.delay += delayTime;
			}

			// When the buffer is full, it drops the packet and icrements the
			// dropped packets counter
			if (buffer.size() == maxBufferSize) {
				// Drop packet
				qos30Mbps.packetsLost++;
			}

			// When the buffer's size is 0, there will be no queuing delay as
			// it is being transmitted immediately
			else if (buffer.size() == 0) {
				buffer.push(pairDouble);
				delayTime = 0.0;
				departureTime = buffer.front()[1] / transmissionSpeed;
				currentTime += departureTime;
				buffer.pop();
			}

			// This case checks to see if the buffer is occupied by packets
			// and applies a queuing delay when the packet is finally transmitted
			else if (buffer.size() > 0 || buffer.size() < 100) {
				buffer.push(pairDouble);
				departureTime = (buffer.front()[1] / transmissionSpeed) + delayTime;
				currentTime += departureTime;
				buffer.pop();
			}

			// Clearing the pair
			pairDouble.pop_back();
			pairDouble.pop_back();
		}
    }

    else {
        cerr << "File failed to open." << endl;
		return -1;
    }

    inputFile.close();

	qos30Mbps.packetLoss = ((double)qos30Mbps.packetsLost / (double)packets) * 100.0;
	qos30Mbps.averageDelay = qos30Mbps.delay / (double)packets;


	cout << "|Speed in Mbps|\t|Average packet loss|\t|Average queuing delay|" << endl;
	cout << " 11\t\t " << qos11Mbps.packetLoss << "%\t\t\t " << qos11Mbps.averageDelay * 1000 << " ms" << endl;
	cout << " 6\t\t " << qos6Mbps.packetLoss << "%\t\t\t " << qos6Mbps.averageDelay * 1000 << " ms"  <<endl;
	cout << " 54\t\t " << qos54Mbps.packetLoss << "%\t\t\t " << qos54Mbps.averageDelay * 1000 << " ms" << endl;
	cout << " 30\t\t " << qos30Mbps.packetLoss << "%\t\t\t " << qos30Mbps.averageDelay * 1000 << " ms" << endl;


    return 0;
}
