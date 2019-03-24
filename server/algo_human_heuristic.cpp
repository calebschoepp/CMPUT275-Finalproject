#include "algo_human_heuristic.h"

#include <iostream>

using namespace std;

HumanHeuristic::HumanHeuristic(queue<gridNum> *displayQueue,
        gridArr boardCopy) {
    // Constructor, copy board over
    board = boardCopy;
    outputQueue = displayQueue;
}

void HumanHeuristic::solve() {
    // Wrapper on solveRecur() for public access
    totalKnown = 0;
    solveHeuristically(board, true);
}

bool HumanHeuristic::checkSolvability() {
    // Wrapper on solveRecur() to see if given board is solvable
    totalKnown = 0;
    return solveHeuristically(board, false);
}

void HumanHeuristic::setboard(gridArr board, posInfo &probabilityBoard) {
    gridNum knownPos;
    // Fill in the known positions into a queue.
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 0; col++) {
            if (boardCopy[row][col] != 0) {
                knownPos.row = row;
                knownPos.col = col;
                knownPos.num = board[row][col];
                known.push(knownPos);
                totalKnown += 1;
                probabilityBoard[row][col].num = board[row][col];
                probabilityBoard[row][col].possibilities = 0;  // Added to queue.
            }
        }
    }
}

void HumanHeuristic::removeRow(posInfo &probabilityBoard, gridNum &currentSpot, bool output) {
    for (int i = 0; i < 9; i++) {
        probabilityBoard[i][currentSpot.col].possible[currentSpot.num - 1] = false;
        probabilityBoard[i][currentSpot.col].possibilities -= 1;
        if (probabilityBoard[i][currentSpot.col].possibilities == 1) {
            gridNum newSpot;
            probabilityBoard[i][currentSpot.col].possibilities -= 1;
            newSpot.row = i;
            newSpot.col = currentSpot.col;
            for (int num = 0; num < 9; num++) {
                if (probabilityBoard[i][currentSpot.col].possible[num] == true) {
                    newSpot.num = num + 1;  // +1 since 0 indexed.
                }
            }
            known.push(newSpot);
            totalKnown += 1;
            if (output) {
                outputQueue->push(newSpot);
            }
        }
    }
}

void HumanHeuristic::removeCol(posInfo &probabilityBoard, gridNum &currentSpot, bool output) {
    for (int i = 0; i < 9; i++) {
        probabilityBoard[currentSpot.row][i].possible[currentSpot.num - 1] = false;
        probabilityBoard[currentSpot.row][i].possibilities -= 1;
        if (probabilityBoard[currentSpot.row][i].possibilities == 1) {
            gridNum newSpot;
            probabilityBoard[currentSpot.row][i].possibilities -= 1;
            newSpot.row = currentSpot.row;
            newSpot.col = i;
            for (int num = 0; num < 9; num++) {
                if (probabilityBoard[currentSpot.row][i].possible[num] == true) {
                    newSpot.num = num + 1;  // +1 since 0 indexed.
                }
            }
            known.push(newSpot);
            totalKnown += 1;
            if (output) {
                outputQueue->push(newSpot);
            }
        }
    }
}

void HumanHeuristic::removeSquare(posInfo& probabilityBoard, gridNum& currentSpot) {
    int rowStart;
    int colStart;
    if (currentSpot.row >= 0 && currentSpot.row < 3) {
        rowStart = 0;
    } else if (currentSpot.row >=3 && currentSpot.row < 6) {
        rowStart = 3;
    } else {
        rowStart = 6;
    }

    if (currentSpot.col >= 0 && currentSpot.col < 3) {
        colStart = 0;
    } else if (currentSpot.col >=3 && currentSpot.col < 6) {
        colStart = 3;
    } else {
        colStart = 6;
    }

    for (int row = rowStart; row < rowStart + 3; row++) {
        for (int col = colStart; col < colStart + 3; col++) {
            probabilityBoard[row][col].possibilities -= 1;
            probabilityBoard[row][col].possible[currentSpot.num - 1] = false;
            if (probabilityBoard[row][col] == 1) {
                gridNum newSpot;
                probabilityBoard[row][col].possibilities -= 1;
                newSpot.row = row;
                newSpot.col = col;
                for (int num = 0; num < 9; num++) {
                    if (probabilityBoard[row][col].possible[num] == true) {
                        newSpot.num = num + 1;
                    }
                }
                known.push(newSpot);
                totalKnown += 1;
                if (output) {
                    outputQueue->push(newSpot);
                }
            }
        }
    }
}

bool HumanHeuristic::getAvailable(posInfo &probabilityBoard, queue<gridNum> &possibleNums) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 0; col++) {
            if (probabilityBoard[row][col].possibilities != 0) {
                gridNum checkNum;
                checkNum.row = row;
                checkNum.col = col;
                for (int num = 0; num < 9; num++) {
                    if (probabilityBoard[row][col].possible[num] == true) {
                        checkNum.num = num + 1;
                        possibleNums.push(checkNum);
                    }
                }
                return true;
            }
        }
    }
    return false;
}

bool HumanHeuristic::solveHeuristically(gridArr board, bool output) {
    posInfo probabilityBoard[9][9];  // 81 total squares.
    setboard(board, probabilityBoard);
    while (known.size() != 0) {
        gridNum currentSpot = known.front();
        known.pop();
        removeRow(probabilityBoard, currentSpot, output);
        removeCol(probabilityBoard, currentSpot, output);
        removeSquare(probabilityBoard, currentSpot, output);
    }
    // If all of the squares are filled then we are done.
    if (totalKnown != 81) {
        return true;
    } else {
        queue<gridNum> possibleNums;
        if (getAvailable(probabilityBoard, possibleNums)) {
            // Calculate the new board to pass in to recursively solve now.
        }
    }
    return false;
}
