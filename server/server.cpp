/*
Names: Robert Mah, Caleb Schoepp
ID: 1532565, 1534577
CCID: rjmah1, cwschoep
CMPUT 275 , Winter 2019

Arduino Sudoku Solver
*/

// includes
#include "serialport.h"
#include "algo_dancing_links.h"
#include "algo_backtracking.h"
#include "algo_human_heuristic.h"
#include "algo_improved_human_heuristic.h"
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>  // for getting runtime of the algorithms.

using namespace std;
using namespace std::chrono;

// Global variables for server. Note: first letter is capitalized for global
// variables.
string Algorithm = "backtracking";  // the current algorithm.
string BoardFileName = "./sudokus/easy-00.txt";  // the current board file path.
queue<gridNum> ChangeQueue;
gridArr Board;  // the current board. Global since any changes need to be saved.

gridArr readInSudoku() {
    /*
    Reads in the sudoku board from the sudoku at the file path specified by
    the global variable BoardFileName.
    */

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
    /*
    Pops the ChangeQueue until it's empty.
    */
    while (!ChangeQueue.empty()) {
        ChangeQueue.pop();
    }
}

void outputChange(SerialPort& Serial, gridNum& change) {
    /*
    Sends the current change through serial communication to the client.
    */

    string outputString;
    outputString = to_string(change.row);
    outputString += ' ';
    outputString += to_string(change.col);
    outputString += ' ';
    outputString += to_string(change.num);
    outputString += '\n';
    cout << "Sending " << outputString;
    Serial.writeline(outputString);
}

void giveChange(SerialPort& Serial) {
    /*
    Gives a change to the client and waits for an acknowledgemnt. If no
    acknowledgement is sent then an error message is displayed on the terminal
    and returns back to the main running of the server.
    */

    gridNum change = ChangeQueue.front();
    ChangeQueue.pop();
    string outputString;
    outputChange(Serial, change);
    string acknowledge;
    acknowledge = Serial.readline(1000);
    cout << "acknowledge " << acknowledge;
    if (acknowledge[0] == 'A') {
        cout << "acknowledged" << endl;
    } else {
        cout << "Error: Did not acknowledge" << endl;
    }

    // debug code.
    string test;
    test = Serial.readline();
    cout << "test row col num " << test;
}

void selectAlgo(string inputString, SerialPort& Serial) {
    /*
    Selects which algorithm is currently selected based on the input string.
    */

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

        case 'D':
            cout << "dancing links algorithm selected" << endl;
            Algorithm = "dancingLinks";
            break;

        case 'I':
            cout << "improved human heuristic algorithm selected" << endl;
            Algorithm = "improvedHumanHeuristic";
            break;

        default:
            cout << "default algorithm selected" << endl;
            Algorithm = "backtracking";
    }
    Serial.writeline("A");  // acknowledge.
}

void sendBoard(SerialPort& Serial) {
    /*
    Sends the current board to the client.
    */

    gridArr board = readInSudoku();  // resets changes from the try it.
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
                cout << "Error: communicating board" << endl;
                error = true;
                break;
            }
        }
        if (error) {
            break;
        }
    }
}

void selectBoard(string inputString, SerialPort& Serial) {
    /*
    Determines which board has been selected from the client. Defaults to the 00
    case if number not properly read, and easy-00 if no difficulty selected.
    */

    char difficulty = inputString[2];
    // Max of 10 sudokus per difficulty.
    int num = inputString[4] - '0';  // converts ascii to int.
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
            cout << "Error: no map selected, default easy-00" << endl;
            BoardFileName = "./sudokus/easy-00.txt";
    }
    sendBoard(Serial);
    Board = readInSudoku();  // sets the new board for the server.
}

void outputTime(SerialPort& Serial, string outputString) {
    /*
    Sends the time it took to solve an algorithm.
    */

    Serial.writeline(outputString);
    cout << "outputString " << outputString;
    string ack = Serial.readline(1000);
    cout << "ack is " << ack;
    if (ack[0] != 'A')  {
        cout << "Error: did not receive acknowledgement." << endl;
    }

    // Show the communication was successful.
    string test = Serial.readline();
    cout << "test time " << test;
}

void solveBacktracking(SerialPort& Serial) {
    /*
    Solve the current Sudoku board using backtracking and send the time it took
    to solve to the client.
    */

    resetChangeQueue();  // empty the ChangeQueue.
    Backtracking solver(&ChangeQueue, Board);
    auto startTime = high_resolution_clock::now();
    solver.solve();
    auto finalTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(finalTime - startTime);
    string outputString = to_string(duration.count());
    outputString += '\n';
    outputTime(Serial, outputString);
    cout << "solved backtracking" << endl;
}

void solveHumanHeuristic(SerialPort& Serial) {
    /*
    Solve the current Sudoku board using human heuristic and send the time it
    took to solve to the client.
    */

    resetChangeQueue();
    HumanHeuristic solver(&ChangeQueue, Board);
    auto startTime = high_resolution_clock::now();
    solver.solve();
    auto finalTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(finalTime - startTime);
    string outputString = to_string(duration.count());
    outputString += '\n';
    outputTime(Serial, outputString);
    cout << "solved humanHeuristic" << endl;
}

void solveDancingLinks(SerialPort& Serial) {
    /*
    Solve the current Sudoku board using dancing links and send the time it
    took to solve to the client.
    */

    resetChangeQueue();
    DancingLinks solver(&ChangeQueue, Board);
    auto startTime = high_resolution_clock::now();
    solver.solve();
    auto finalTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(finalTime - startTime);
    string outputString = to_string(duration.count());
    outputString += '\n';
    outputTime(Serial, outputString);
    cout << "solved dancingLinks" << endl;
}

void solveImprovedHumanHeuristic(SerialPort& Serial) {
    /*
    Solve the current Sudoku board using the improved human heuristic algorithm
    and send the time it took to solve to the client.
    */

    resetChangeQueue();
    ImprovedHumanHeuristic solver(&ChangeQueue, Board);
    auto startTime = high_resolution_clock::now();
    solver.solve();
    auto finalTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(finalTime - startTime);
    string outputString = to_string(duration.count());
    outputString += '\n';
    outputTime(Serial, outputString);
    cout << "solved improvedHumanHeuristic" << endl;
}

void startSolve(SerialPort& Serial) {
    /*
    Find which algorithm is currently selected and call for that algorithm to be
    solved.
    */

    Board = readInSudoku();
    if (Algorithm == "backtracking") {
        cout << "algorithm backtracking" << endl;
        solveBacktracking(Serial);
    } else if (Algorithm == "humanHeuristic") {
        cout << "algorithm humanHeuristic" << endl;
        solveHumanHeuristic(Serial);
    } else if (Algorithm == "dancingLinks") {
        cout << "algorithm dancingLinks" << endl;
        solveDancingLinks(Serial);
    } else if (Algorithm == "improvedHumanHeuristic") {
        cout << "algorithm improvedHumanHeuristic" << endl;
        solveImprovedHumanHeuristic(Serial);
    } else{
        cout << "default algo" << endl;
        solveBacktracking(Serial);
    }
}

void solveSize(SerialPort& Serial) {
    /*
    Send the size of the changeQueue for the client to know how much data to
    read in.
    */

    string size = to_string(ChangeQueue.size());
    size += '\n';
    Serial.writeline(size);
    cout << "size is " << size;
    string ack = Serial.readline(1000);
    cout << "ack is " << ack;
    if (ack[0] != 'A') {
        cout << "Error: communicate solvedSize failed" << endl;
    }

    // Ensure sent message was correct.
    string test = Serial.readline();
    cout << "test solve size " << test;
}

gridNum updateBoard(SerialPort& Serial) {
    /*
    Read in a change from the client and add it to the Board.
    */
    gridNum change;
    string row = Serial.readline(1000);
    change.row = stoi(row);
    string col = Serial.readline(1000);
    change.col = stoi(col);
    string num = Serial.readline(1000);
    change.num = stoi(num);
    cout << "new row " << change.row << endl;
    cout << "new col " << change.col << endl;
    cout << "new num " << change.num << endl;
    Board[change.row][change.col] = change.num;
    return change;
}

void checkSolvability(SerialPort& Serial) {
    /*
    Checks to see if the current board state with the new change is solvable.
    Only uses backtracking for simplicity.
    */
    gridNum change = updateBoard(Serial);
    Backtracking solver(&ChangeQueue, Board);
    bool check = solver.checkSolvability(change.row, change.col,
            change.num);

    if (check) {
        Serial.writeline("1");
    } else {
        Serial.writeline("0");
    }
}

int main() {
    /*
    Handles initial setup for the server and then selects the action to take
    based on the input from the client.
    */
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

            case 'H':
                checkSolvability(Serial);
                break;

            default:
                cout << "error in communication" << endl;
        }
    }
    return 0;
}
