// includes
#include "serialport.h"
#include "algo_dancing_links.h"
#include "algo_backtracking.h"
#include "algo_human_heuristic.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Global variables for server.
string Algorithm = "backtracking";
string BoardFileName = "./sudokus/easy-00.txt";
queue<gridNum> ChangeQueue;

gridArr readInSudoku() {
    gridArr board;
    fstream file;
    file.open(BoardFileName);
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int val;
            file >> val;
            board[row][col] = val;
        }
    }
    return board;
}

void resetChangeQueue() {
    while (!ChangeQueue.empty()) {
        ChangeQueue.pop();
    }
}

void giveChange(SerialPort& Serial) {
    gridNum change = ChangeQueue.front();
    ChangeQueue.pop();
    string outputString;
    outputString = to_string(change.row);
    outputString += ' ';
    outputString += to_string(change.col);
    outputString += ' ';
    outputString += to_string(change.num);
    outputString += '\n';
    cout << "Sending " << outputString;
    Serial.writeline(outputString);
    // now wait for ack.
    string acknowledge;
    acknowledge = Serial.readline(1000);
    cout << "acknowledge " << acknowledge;
    if (acknowledge[0] == 'A') {
        cout << "acknowledged" << endl;
    } else {
        cout << "Did not acknowledge" << endl;
    }
    string test;
    test = Serial.readline();
    cout << "test row col num " << test;
}

void selectAlgo(string inputString, SerialPort& Serial) {
    char newAlgo = inputString[2];
    switch(newAlgo) {
        case 'B':
            cout << "backtracking algorithm selected" << endl;
            Algorithm = "backtracking";
            break;
        case 'H':
            cout << "human heuristic algorithm selected" << endl;
            Algorithm = "humanHeuristic";
            break;
        default:
            cout << "default algorithm selected" << endl;
            Algorithm = "backtracking";
    }
    // if (inputString[2] == 'B') {
    //     Algorithm = "backtracking";
    // } else {
    //     cout << "no valid algorithm selected" << endl;
    //     Algorithm = "backtracking";
    // }
    cout << "writing ack algo" << endl;
    Serial.writeline("A");
}

void sendBoard(SerialPort& Serial) {
    gridArr board = readInSudoku();
    bool error = false;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            string currentPos = to_string(row);
            currentPos += ' ';
            currentPos += to_string(col);
            currentPos += ' ';
            currentPos += to_string(board[row][col]);
            currentPos += '\n';
            Serial.writeline(currentPos);
            string ack = Serial.readline(1000);
            cout << "ack is " << ack << endl;
            if (ack[0] == 'A') {
                continue;
            } else {
                cout << "error communicating board" << endl;
                error = true;
                break;
            }
        }
        if (error) {
            break;
        }
    }
    if (error) {
        sendBoard(Serial);  // retry sending board.
    }
}

void selectBoard(string inputString, SerialPort& Serial) {
    char difficulty = inputString[2];
    int num = inputString[4] - '0';
    switch(difficulty) {
        case 'E':
            switch(num) {
                case 0:
                    cout << "in easy 0 case" << endl;
                    BoardFileName = "./sudokus/easy-00.txt";
                    break;
                case 1:
                    cout << "in easy 1 case" << endl;
                    BoardFileName = "./sudokus/easy-01.txt";
                    break;
                case 2:
                    BoardFileName = "./sudokus/easy-02.txt";
                    break;
                default:
                    cout << "default easy map selected" << endl;
                    BoardFileName = "./sudokus/easy-00.txt";
            }
            break;

        case 'M':
            switch(num) {
                case 0:
                    BoardFileName = "./sudokus/med-00.txt";
                    break;
                case 1:
                    BoardFileName = "./sudokus/med-01.txt";
                    break;
                default:
                    cout << "default medium map selected" << endl;
                    BoardFileName = "./sudokus/med-00.txt";
            }
            break;

        case 'H':
            switch(num) {
                case 0:
                    BoardFileName = "./sudokus/hard-00.txt";
                    break;
                case 1:
                    BoardFileName = "./sudokus/hard-01.txt";
                    break;
                case 2:
                    BoardFileName = "./sudokus/hard-02.txt";
                    break;
                case 3:
                    BoardFileName = "./sudokus/hard-03.txt";
                    break;
                default:
                    cout << "default hard map selected" << endl;
                    BoardFileName = "./sudokus/hard-00.txt";
            }
            break;

        default:
            cout << "default map selected" << endl;
            BoardFileName = "./sudokus/easy-00.txt";
    }
    // if(inputString[2] == 'E') {
    //     if (inputString[4] == '0') {
    //         BoardFileName = "./sudokus/easy-00.txt";
    //     } else if (inputString[4] == ) {
    //
    //     }else {
    //         BoardFileName = "./sudokus/easy-00.txt";
    //     }
    // } else if (inputString[2] == 'M') {
    //     if (inputString[4] == '0') {
    //         BoardFileName = "./sudokus/med-00.txt";
    //     } else {
    //         BoardFileName = "./sudokus/med-00.txt";
    //     }
    // } else if (inputString[2] == 'H') {
    //     if (inputString[4] == '0') {
    //         BoardFileName = "./sudokus/hard-00.txt";
    //     } else if (inputString[4] == '1') {
    //         BoardFileName = "./sudokus/hard-01.txt";
    //     } else if (inputString[4] == '2') {
    //         BoardFileName = "./sudokus/hard-02.txt";
    //     } else if (inputString[4] == '3') {
    //         BoardFileName = "./sudokus/hard-03.txt";
    //     } else {
    //         BoardFileName = "./sudokus/hard-00.txt";
    //     }
    // } else {
    //     cout << "no valid sudoku board selected" << endl;
    //     BoardFileName = "./sudokus/easy-00.txt";
    // }
    sendBoard(Serial);
}

void solveBacktracking(SerialPort& Serial) {
    gridArr board = readInSudoku();
    cout << "Board " << BoardFileName << endl;
    resetChangeQueue();
    Backtracking solver(&ChangeQueue, board);
    auto startTime = high_resolution_clock::now();
    solver.solve();
    auto finalTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(finalTime - startTime);
    string outputString = to_string(duration.count());
    outputString += '\n';
    Serial.writeline(outputString);
    cout << "outputString " << outputString;
    string ack = Serial.readline(1000);
    cout << "ack is " << ack;
    if (ack[0] != 'A')  {
        cout << "error trying to solveBacktracking, retrying" << endl;
        solveBacktracking(Serial);
    }
    string test = Serial.readline(1000);
    cout << "test time " << test;
    cout << "solved backtracking" << endl;
}

void solveHumanHeuristic(SerialPort& Serial) {
    gridArr board = readInSudoku();
    cout << "Board " << BoardFileName << endl;
    resetChangeQueue();
    HumanHeuristic solver(&ChangeQueue, board);
    auto startTime = high_resolution_clock::now();
    solver.solve();
    auto finalTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(finalTime - startTime);
    string outputString = to_string(duration.count());
    outputString += '\n';
    cout << "outputString " << outputString;
    Serial.writeline(outputString);
    string ack = Serial.readline(1000);
    cout << "ack is " << ack << endl;
    if (ack[0] != 'A')  {
        cout << "error trying to solveBacktracking, retrying" << endl;
        solveHumanHeuristic(Serial);
    }
    string test = Serial.readline(1000);
    cout << "test time " << test;
    cout << "solved humanHeuristic" << endl;
}

void startSolve(SerialPort& Serial) {
    if (Algorithm == "backtracking") {
        cout << "algorithm backtracking" << endl;
        solveBacktracking(Serial);
    } else if (Algorithm == "humanHeuristic") {
        cout << "algorithm humanHeuristic" << endl;
        solveHumanHeuristic(Serial);
    } else {
        cout << "default algo" << endl;
        solveBacktracking(Serial);
    }
}

void solveSize(SerialPort& Serial) {
    string size = to_string(ChangeQueue.size());
    size += '\n';
    Serial.writeline(size);
    cout << "size is " << size;
    string ack = Serial.readline(1000);
    cout << "ack is " << ack;
    if (ack[0] != 'A') {
        cout << "errror trying to communicate solvedSize, retrying" << endl;
        solveSize(Serial);
    }
    // right now size isn't right client side.
    string test = Serial.readline();
    cout << "test solve size " << test;
}

int main() {
    // Simple state machine based on initial input from serial
    // Timeouts bring back to main function

    // State variables
    // int ...
    // bool ....
    SerialPort Serial("/dev/ttyACM0");
    Serial.readline(50);  // Remove any leftover bytes in the buffer.
    while (true) {
        string inputString;
        cout << "waiting for input" << endl;
        inputString = Serial.readline();  // waits for any input from client.
        cout << "input is " << inputString << endl;
        char select = inputString[0];
        switch(select) {

            case 'C':
                giveChange(Serial);
                break;

            case 'L':
                selectAlgo(inputString, Serial);
                break;

            case 'B':
                selectBoard(inputString, Serial);
                break;

            case 'S':
                startSolve(Serial);
                break;

            case 'I':
                solveSize(Serial);
                break;

            default:
                cout << "error in communication" << endl;
        }
        // if (inputString[0] == 'C') {
        //     giveChange(Serial);
        // } else if (inputString[0] == 'L') {
        //     selectAlgo(inputString, Serial);
        // } else if (inputString[0] == 'B') {
        //     selectBoard(inputString, Serial);
        // } else if (inputString[0] == 'S') {
        //     startSolve(Serial);
        // } else if (inputString[0] == 'I') {
        //     solveSize(Serial);
        // } else {
        //     cout << "error in communication" << endl;
        // }
    }
    return 0;
}
