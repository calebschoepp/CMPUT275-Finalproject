/*
Names: Robert Mah, Caleb Schoepp
ID: 1532565, 1534577
CCID: rjmah1, cwschoep
CMPUT 275 , Winter 2019

Arduino Sudoku Solver
*/


#include "algo_backtracking.h"

#include <iostream>

Backtracking::Backtracking(std::queue<gridNum> *displayQueue,
        gridArr boardCopy) {
    // Constructor, copy board over
    board = boardCopy;
    outputQueue = displayQueue;
}

void Backtracking::solve() {
    // Wrapper on solveRecur() for public access
    solveRecur(board, true);
}

bool Backtracking::checkSolvability(int row, int col, int num) {
    // Wrapper on solveRecur() to see if given board is solvable
    // Takes in row col and num of what is to be checked
    // and first checks if that is solvable before calling recursive part
    board[row][col] = 0;
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            if(board[x][y] != 0) {
                int check = board[x][y];
                board[x][y] = 0;
                if (!cellPermitted(board, x, y, check)) {
                    return false;
                } else {
                    board[x][y] = check;
                }
            }
        }
    }
    if (!cellPermitted(board, row, col, num) && num != 0) {
        cout << "returned false" << endl;
        return false;
    }

    cout << "solving recursively" << endl;
    board[row][col] = num;
    return solveRecur(board, false);
}

bool Backtracking::solveRecur(gridArr board, bool output) {
    // Output to be true if it should output to outputQueue
    // Pass board by value to remember changes for backtracking

    // Get a new location
    std::pair<int, int> newCell = newLocation(board);

    if (newCell == FULL) {
        // The grid is full and thus it is solved
        return true;
    }

    for (int numAttempt = 1; numAttempt <= 9; ++numAttempt) {
        if (cellPermitted(board, newCell.first, newCell.second, numAttempt)) {
            // As far as we know the number works where it is
            board[newCell.first][newCell.second] = numAttempt;

            // Output to queue for serial comms
            if (output) {
                gridNum change;
                change.row = newCell.first;
                change.col = newCell.second;
                change.num = numAttempt;
                outputQueue->push(change);
            }

            if (solveRecur(board, output)) {
                return true;
            }
            // If we get here we have backtracked and the number didn't work
            // Try again with a new number

            // All numbers attempted have failed and we must backtrack
            // Set the cell to blank (0)
            board[newCell.first][newCell.second] = 0;

            // Output to queue for serial comms
            if (output) {
                gridNum change;
                change.row = newCell.first;
                change.col = newCell.second;
                change.num = 0;
                outputQueue->push(change);
            }
        }
    }
    return false;
}

bool Backtracking::cellPermitted(const gridArr &board, int row, int col, int num) {
    // Test if a particular number is permitted in a particular cell given a board state
    if (!rowPermitted(board, row, num)) {
        return false;
    } else if (!colPermitted(board, col, num)) {
        return false;
    } else if (!squarePermitted(board, row, col, num)) {
        return false;
    }
    return true;
}

bool Backtracking::rowPermitted(const gridArr &board, int row, int num) {
    // Return true if num is not found in row of board
    for (int col = 0; col < 9; ++col) {
        if (board[row][col] == num) {
            return false;
        }
    }
    return true;
}

bool Backtracking::colPermitted(const gridArr &board, int col, int num) {
    // Return true if num is not found in col of board
    for (int row = 0; row < 9; ++row) {
        if (board[row][col] == num) {
            return false;
        }
    }
    return true;
}

bool Backtracking::squarePermitted(const gridArr &board, int realRow, int realCol, int num) {
    // Return true if num is not found in given square of the board
    int rowStart = -1;
    int colStart = -1;

    // Determine the bounds to check within for the particular square
    if (realRow >= 0 && realRow < 3) {
        rowStart = 0;
    } else if (realRow >= 3 && realRow < 6) {
        rowStart = 3;
    } else {
        rowStart = 6;
    }

    if (realCol >= 0 && realCol < 3) {
        colStart = 0;
    } else if (realCol >= 3 && realCol < 6) {
        colStart = 3;
    } else {
        colStart = 6;
    }

    // Error checking
    if (rowStart == -1 || colStart == -1) {
        return false;
    }

    // Now actually check for duplicates in the square
    for (int row = rowStart; row < rowStart + 3; ++row) {
        for (int col = colStart; col < colStart + 3; ++col) {
            if (board[row][col] == num) {
                return false;
            }
        }
    }
    return true;
}

std::pair<int, int> Backtracking::newLocation(gridArr board) {
    // Return a pair with an empty cell to be filled
    // Return a pair <-1, -1> if the board is full
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            if (board[row][col] == 0) {
                return std::make_pair(row, col);
            }
        }
    }
    // No empty squares
    return std::make_pair(-1, -1);
}
