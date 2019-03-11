#include "algo_dfs.h"

#include <iostream>

Dfs::Dfs(std::queue<gridNum> *displayQueue,
        gridArr boardCopy) {
    // Constructor, copy board over
    board = boardCopy;
    outputQueue = displayQueue;
}

Dfs::~Dfs() {

}

void Dfs::solve() {
    // Wrapper on solveRecur() for public access
    solveRecur(board, true);
}

bool Dfs::checkSolvability() {
    // Wrapper on solveRecur() to see if given board is solvable
    return solveRecur(board, false);
}

bool Dfs::solveRecur(gridArr board, bool output) {
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
        
    // // All numbers attempted have failed and we must backtrack
    // // Set the cell to blank (0)
    // board[newCell.first][newCell.second] = 0;

    // // Output to queue for serial comms
    // if (output) {
    //     gridNum change;
    //     change.row = newCell.first;
    //     change.col = newCell.second;
    //     change.num = 0;
    //     outputQueue->push(change);  
    // }

    return false;
}

bool Dfs::cellPermitted(const gridArr &board, int row, int col, int num) {
    if (!rowPermitted(board, row, num)) {
        return false;
    } else if (!colPermitted(board, col, num)) {
        return false;
    } else if (!squarePermitted(board, row, col, num)) {
        return false;
    }
    return true;
}

bool Dfs::rowPermitted(const gridArr &board, int row, int num) {
    // Return true if num is not found in row of board
    for (int col = 0; col < 9; ++col) {
        if (board[row][col] == num) {
            return false;
        }
    }
    return true;
}

bool Dfs::colPermitted(const gridArr &board, int col, int num) {
    // Return true if num is not found in col of board
    for (int row = 0; row < 9; ++row) {
        if (board[row][col] == num) {
            return false;
        }
    }
    return true;
}

bool Dfs::squarePermitted(const gridArr &board, int realRow, int realCol, int num) {
    // Return true if num is not found in given square of the board
    int row_start = -1;
    int col_start = -1;

    if (realRow >= 0 && realRow < 3) {
        row_start = 0;
    } else if (realRow >= 3 && realRow < 6) {
        row_start = 3;
    } else {
        row_start = 6;
    }

    if (realCol >= 0 && realCol < 3) {
        col_start = 0;
    } else if (realCol >= 3 && realCol < 6) {
        col_start = 3;
    } else {
        col_start = 6;
    }

    if (row_start == -1 || col_start == -1) {
        return false;
    }

    for (int row = row_start; row < row_start + 3; ++row) {
        for (int col = col_start; col < col_start + 3; ++col) {
            if (board[row][col] == num) {
                return false;
            }
        }
    }
    return true;
}

std::pair<int, int> Dfs::newLocation(gridArr board) {
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