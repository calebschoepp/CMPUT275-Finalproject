/*
Names: Robert Mah, Caleb Schoepp
ID: 1532565, 1534577
CCID: rjmah1, cwschoep
CMPUT 275 , Winter 2019

Arduino Sudoku Solver
*/

#include "algo_human_heuristic.h"

#include <iostream>

using namespace std;

HumanHeuristic::HumanHeuristic(queue<gridNum> *displayQueue,
        gridArr boardCopy) {
    // Constructor, copy board over.

    board = boardCopy;
    outputQueue = displayQueue;
}

void HumanHeuristic::solve() {
    // Wrapper on solveRecur() for public access.

    totalKnown = 0;
    solveHeuristically(board, true);
}

bool HumanHeuristic::checkSolvability() {
    // Wrapper on solveRecur() to see if given board is solvable.

    totalKnown = 0;
    return solveHeuristically(board, false);
}

void HumanHeuristic::removeAll(posInfo (&probBoard)[9][9], gridNum &curSpot,
        bool output) {
    // Removes the value from the row, column, and square where the number is
    // contained.

    removeRow(probBoard, curSpot, output);
    removeCol(probBoard, curSpot, output);
    removeSquare(probBoard, curSpot, output);
}

void HumanHeuristic::setboard(gridArr board, posInfo (&probBoard)[9][9]) {
    // Fills in all of the non zero elements of the board into a probability
    // board and appends the values to the queue of known values to be
    // processed.

    gridNum knownPos;
    // Fill in the known positions into a queue.
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] != 0) {
                knownPos.row = row;
                knownPos.col = col;
                knownPos.num = board[row][col];
                known.push(knownPos);
                totalKnown += 1;
                probBoard[row][col].num = board[row][col];
                probBoard[row][col].possibilities = 0;
            }
        }
    }
}

void HumanHeuristic::checkPos(posInfo (&probBoard)[9][9], int row, int col,
        bool output) {
    /*
    Checks if the number of possibilities at a position is 1, if it is then
    that value is known so it finds the value and adds it to the output
    queue. Also calls for that value to be removed from the board (runs in
    the middle to prevent the row and col this value is in from having the
    value be true.)
    */

    if (probBoard[row][col].possibilities == 1) {
        gridNum newSpot;
        probBoard[row][col].possibilities -= 1;
        newSpot.row = row;
        newSpot.col = col;
        // finds the value for that position
        for (int val = 0; val < 9; val++) {
            if (probBoard[row][col].possible[val] == true) {
                newSpot.num = val + 1;  // +1 since 0 indexed.
                probBoard[row][col].num = val + 1;
            }
        }
        removeAll(probBoard, newSpot, output);
        totalKnown += 1;
        if (output) {
            outputQueue->push(newSpot);
        }
    }
}

void HumanHeuristic::removeRow(posInfo (&probBoard)[9][9], gridNum &curSpot,
        bool output) {
    // Removes the number at the current spot from its row.

    for (int i = 0; i < 9; i++) {
        if (probBoard[i][curSpot.col].possible[curSpot.num - 1]) {
            probBoard[i][curSpot.col].possible[curSpot.num - 1] = false;
            probBoard[i][curSpot.col].possibilities -= 1;
            checkPos(probBoard, i, curSpot.col, output);
        }
    }
}

void HumanHeuristic::removeCol(posInfo (&probBoard)[9][9], gridNum &curSpot,
        bool output) {
    // Removes the number at the currenst spot from its column.

    for (int i = 0; i < 9; i++) {
        if (probBoard[curSpot.row][i].possible[curSpot.num - 1]) {
            probBoard[curSpot.row][i].possible[curSpot.num - 1] = false;
            probBoard[curSpot.row][i].possibilities -= 1;
            checkPos(probBoard, curSpot.row, i, output);
        }
    }
}

void HumanHeuristic::removeSquare(posInfo (&probBoard)[9][9], gridNum& curSpot,
        bool output) {
    // Removes the number at the current spot from the square containing it.

    int rowStart;
    int colStart;
    if (curSpot.row >= 0 && curSpot.row < 3) {
        rowStart = 0;
    } else if (curSpot.row >=3 && curSpot.row < 6) {
        rowStart = 3;
    } else {
        rowStart = 6;
    }

    if (curSpot.col >= 0 && curSpot.col < 3) {
        colStart = 0;
    } else if (curSpot.col >=3 && curSpot.col < 6) {
        colStart = 3;
    } else {
        colStart = 6;
    }

    for (int row = rowStart; row < rowStart + 3; row++) {
        for (int col = colStart; col < colStart + 3; col++) {
            if (probBoard[row][col].possible[curSpot.num - 1]) {
                probBoard[row][col].possibilities -= 1;
                probBoard[row][col].possible[curSpot.num - 1] = false;
                checkPos(probBoard, row, col, output);
            }
        }
    }
}

bool HumanHeuristic::solveHeuristically(gridArr board, bool output) {
    // solves the sudoku board using the human heuristic algorithm. If the
    // board can be completely filled it returns true, otherwise it returns
    // false with all known values appended to the outputQueue.

    posInfo probBoard[9][9];  // 81 total squares.
    setboard(board, probBoard);
    while (known.size() != 0) {
        // cout << "in while loop" << endl;
        gridNum currentSpot = known.top();
        known.pop();
        removeAll(probBoard, currentSpot, output);
    }
    // If all of the squares are filled then we are done.
    if (totalKnown == 81) {
        return true;
    }

    return false;
}
