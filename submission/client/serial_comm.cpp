/*
Names: Robert Mah, Caleb Schoepp
ID: 1532565, 1534577
CCID: rjmah1, cwschoep
CMPUT 275 , Winter 2019

Arduino Sudoku Solver
*/


#include "serial_comm.h"

// maximum length that a read would be.
#define MAX_POINT_STR_LEN 10
#define MAX_TIME_STR_LEN 25

// Globally shared state variables
extern shared_vars shared;

SerialComm::SerialComm() {
    // Constructor that initializes the serial port.
    Serial.begin(9600);
    Serial.flush();
}

bool SerialComm::getChange(point_change *change) {
// Get the changed point 1 point at a time.
// Case 'C'.
    Serial.print("C\n");
    Serial.flush();
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

            // Send the point back to the server to ensure it's correct.
            Serial.print(change->row);
            Serial.print(" ");
            Serial.print(change->col);
            Serial.print(" ");
            Serial.print(change->num);
            Serial.print("\n");
            Serial.flush();
            return true;
        }
    }
    return false;
}

void SerialComm::selectAlgo() {
// selects the algorithm based on the consts and types algo.
// case 'L'
    switch (shared.algorithm) {
        case BACKTRACKING:
            Serial.print("L B\n");
            Serial.flush();
            break;
        case HUMAN_HEURISTIC:
            Serial.print("L H\n");
            Serial.flush();
            break;
        case DANCING_LINKS:
            Serial.print("L D\n");
            Serial.flush();
            break;
        case IMPROVED_HUMAN_HEURISTIC:
            Serial.print("L I\n");
            Serial.flush();
            break;
        default:  // default case is the backtracking case.
            Serial.print("L B\n");
            Serial.flush();
    }
    bool complete = false;
    unsigned long startTime = millis();

    // receive the acknowledgement.
    while (millis() - startTime < 1000) {
        if (Serial.available() > 0) {
            char acknowledge;
            acknowledge = Serial.read();
            if (acknowledge == 'A') {
                complete = true;
                break;
            }
        }
    }
    if (!complete) {
        selectAlgo();
    }
}

void SerialComm::sendBoardMessage() {
    // Sends the current selected board to the server.
    Serial.print("B ");
    switch (shared._board_type) {
        case EASY_00:
            Serial.print("E 0");
            break;
        case EASY_01:
            Serial.print("E 1");
            break;
        case EASY_02:
            Serial.print("E 2");
            break;
        case MED_00:
            Serial.print("M 0");
            break;
        case MED_01:
            Serial.print("M 1");
            break;
        case HARD_00:
            Serial.print("H 0");
            break;
        case HARD_01:
            Serial.print("H 1");
            break;
        case HARD_02:
            Serial.print("H 2");
            break;
        case HARD_03:
            Serial.print("H 3");
            break;
        default:  // Puts the EASY_00 board as default.
            Serial.print("E 0");
    }
    Serial.print("\n");
    Serial.flush();
}

void SerialComm::selectBoard(point_change (&changes)[81]) {
// selects the board based on the consts and types board and gets the resulting
// board as the point_change array with 81 points for the 9x9 board.
// case 'B'
    sendBoardMessage();
    int pos = 0;
    bool complete = false;
    unsigned long startTime = millis();
    while (millis() - startTime < 1000) {
        if (Serial.available() > 0) {
            char input[MAX_POINT_STR_LEN] = {};
            Serial.readBytesUntil('\n', input, MAX_POINT_STR_LEN);
            char* currentString;
            currentString = strtok(input, " ");
            changes[pos].row = atoi(currentString);
            currentString = strtok(NULL, " ");
            changes[pos].col = atoi(currentString);
            currentString = strtok(NULL, "\n");
            changes[pos].num = atoi(currentString);
            pos++;
            startTime = millis();
            Serial.print("A\n");
            Serial.flush();
            if (pos == 81) {
                complete = true;
                break;
            }
        }
    }
    if (!complete) {
        selectBoard(changes);
    }
}

long int SerialComm::solve() {
// call for the server to solve. Return the time it took to solve.
// case 'S'
    Serial.print("S\n");
    Serial.flush();
    unsigned long startTime = millis();
    while (millis() - startTime < 10000) {  // Gives the server 10s to respond.
        if (Serial.available() > 0) {
            char input[MAX_TIME_STR_LEN] = {};
            Serial.readBytesUntil('\n', input, MAX_TIME_STR_LEN);
            char* currentString;
            currentString = strtok(input, "\n");
            long int time = atol(currentString);
            Serial.print("A\n");
            Serial.flush();

            // resend time to ensure it's correct server side.
            Serial.print(time);
            Serial.print("\n");
            Serial.flush();
            return time;  // returns if successful.
        }
    }
    solve();  // calls for the server to solve again (timeout).
    return 0;  // should never return 0.
}

long int SerialComm::solvedSize() {
// pings the server to return the number of points in the output queue.
// case 'I'
    Serial.print("I\n");
    Serial.flush();
    unsigned long startTime = millis();
    while (millis() - startTime < 1000) {
        if (Serial.available() > 0) {
            char input[MAX_TIME_STR_LEN] = {};
            Serial.readBytesUntil('\n', input, MAX_TIME_STR_LEN);
            char* currentString;
            currentString = strtok(input, "\n");
            long int size = atol(currentString);
            Serial.print("A\n");
            Serial.flush();

            // resend size to confirm it's correct server side.
            Serial.print(size);
            Serial.print("\n");
            Serial.flush();
            return size;
        }
    }
    solvedSize();  // timeout so it calls the server again.
    return 0;
}

void SerialComm::sendChange(point_change change) {
    // Sends the change to the server.
    Serial.print(change.row);
    Serial.print("\n");
    Serial.flush();
    Serial.print(change.col);
    Serial.print("\n");
    Serial.flush();
    Serial.print(change.num);
    Serial.print("\n");
    Serial.flush();
}

bool SerialComm::checkSolvability(point_change change) {
    // Sends a message to the server to check whether the change made creates a
    // solvable board state.
    Serial.print("H\n");
    Serial.flush();
    sendChange(change);
    unsigned long startTime = millis();
    while (millis() - startTime < 1000) {
        if (Serial.available() > 0) {
            char check;
            check = Serial.read();
            if (check == '1') {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}
