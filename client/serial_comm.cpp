#include "serial_comm.h"

#define MAX_POINT_STR_LEN 10  // maximum length that a read would be.

SerialComm::SerialComm() {
    Serial.begin(9600);
    Serial.flush();
}

bool SerialComm::getChange(point_change *change) {
// get the changed point 1 point at a time
// case 'C'
    unsigned long startTime = millis();
    while (millis() - startTime < 1000) {
        if (Serial.available() > 0) {
            char input[MAX_POINT_STR_LEN] = {};
            Serial.readBytesUntil('\n', input, MAX_POINT_STR_LEN);
            char* currentString;
            currentString = strtok(input, " ");
            change->row = atoi(currentString);
            currentString = strtok(NULL, " ");
            change->col = atoi(currentString);
            currentString = strtok(NULL, "\n");
            change->num = atoi(currentString);
            Serial.print("A\n");
            Serial.flush();
            return true;
        }
    }
    return false;
}

void SerialComm::selectAlgo() {
// selects the algorithm based on the consts and types algo.
// case 'L'
}

void SerialComm::selectBoard(point_change changes[81]) {
// selects the board based on the consts and types board and gets the resulting
// board as the point_change array with 81 points for the 9x9 board.
// case 'B'
}

void SerialComm::solve() {
// call for the server to solve.
// case 'S'
}

void SerialComm::solvedSize() {
// pings the server to return the number of points in the output queue.
// case 'I'
}
