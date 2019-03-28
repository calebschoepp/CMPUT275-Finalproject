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
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            memo[row][col] = false;
        }
    }
    cout << "solving" << endl;
    solveHeuristically(board, true, totalKnown);
}

bool HumanHeuristic::checkSolvability() {
    // Wrapper on solveRecur() to see if given board is solvable
    totalKnown = 0;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            memo[row][col] = false;
        }
    }
    return solveHeuristically(board, false, totalKnown);
}

void HumanHeuristic::setboard(gridArr board, posInfo (&probabilityBoard)[9][9]) {
    cout << "setting board" << endl;
    gridNum knownPos;
    // Fill in the known positions into a queue.
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] != 0) {
                knownPos.row = row;
                knownPos.col = col;
                knownPos.num = board[row][col];
                cout << "row " << knownPos.row;
                cout << " col " << knownPos.col;
                cout << " num " << knownPos.num << endl;
                known.push(knownPos);
                totalKnown += 1;
                probabilityBoard[row][col].num = board[row][col];
                probabilityBoard[row][col].possibilities = 0;  // Added to queue.
            }
        }
    }
}

void HumanHeuristic::removeRow(posInfo (&probabilityBoard)[9][9], gridNum &currentSpot, bool output) {
    for (int i = 0; i < 9; i++) {
        if (probabilityBoard[i][currentSpot.col].possible[currentSpot.num - 1]) {
            probabilityBoard[i][currentSpot.col].possible[currentSpot.num - 1] = false;
            probabilityBoard[i][currentSpot.col].possibilities -= 1;
            if (probabilityBoard[i][currentSpot.col].possibilities == 1) {
                gridNum newSpot;
                probabilityBoard[i][currentSpot.col].possibilities -= 1;
                newSpot.row = i;
                newSpot.col = currentSpot.col;
                for (int val = 0; val < 9; val++) {
                    if (probabilityBoard[i][currentSpot.col].possible[val] == true) {
                        cout << "got true" << endl;
                        cout << val + 1 << endl;
                        newSpot.num = val + 1;  // +1 since 0 indexed.
                        probabilityBoard[i][currentSpot.col].num = val + 1;
                    }
                }
                cout << "newSpot.row " <<  newSpot.row;
                cout << " newSpot.col " << newSpot.col;
                cout << " newSpot.num " << newSpot.num << endl;
                cout << "removed row" << endl;
                removeRow(probabilityBoard, newSpot, output);
                cout << "removed col" << endl;
                removeCol(probabilityBoard, newSpot, output);
                cout << "removed square" << endl;
                removeSquare(probabilityBoard, newSpot, output);
                known.push(newSpot);
                totalKnown += 1;
                if (output) {
                    cout << "pushing" << endl;
                    outputQueue->push(newSpot);
                }
            }
        }
    }
}

void HumanHeuristic::removeCol(posInfo (&probabilityBoard)[9][9], gridNum &currentSpot, bool output) {
    for (int i = 0; i < 9; i++) {
        if (probabilityBoard[currentSpot.row][i].possible[currentSpot.num - 1]) {
            probabilityBoard[currentSpot.row][i].possible[currentSpot.num - 1] = false;
            probabilityBoard[currentSpot.row][i].possibilities -= 1;
            if (probabilityBoard[currentSpot.row][i].possibilities == 1) {
                gridNum newSpot;
                probabilityBoard[currentSpot.row][i].possibilities -= 1;
                newSpot.row = currentSpot.row;
                newSpot.col = i;
                for (int val = 0; val < 9; val++) {
                    if (probabilityBoard[currentSpot.row][i].possible[val] == true) {
                        cout << "got true" << endl;
                        cout << val + 1 << endl;
                        probabilityBoard[currentSpot.row][i].num = val + 1;
                        newSpot.num = val + 1;  // +1 since 0 indexed.
                    }
                }
                cout << "newSpot.row " <<  newSpot.row;
                cout << " newSpot.col " << newSpot.col;
                cout << " newSpot.num " << newSpot.num << endl;
                cout << "removed row" << endl;
                removeRow(probabilityBoard, newSpot, output);
                cout << "removed col" << endl;
                removeCol(probabilityBoard, newSpot, output);
                cout << "removed square" << endl;
                removeSquare(probabilityBoard, newSpot, output);
                known.push(newSpot);
                totalKnown += 1;
                if (output) {
                    outputQueue->push(newSpot);
                }
            }
        }
    }
}

void HumanHeuristic::removeSquare(posInfo (&probabilityBoard)[9][9], gridNum& currentSpot, bool output) {
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
            if (probabilityBoard[row][col].possible[currentSpot.num - 1]) {
                probabilityBoard[row][col].possibilities -= 1;
                probabilityBoard[row][col].possible[currentSpot.num - 1] = false;
                if (probabilityBoard[row][col].possibilities == 1) {
                    gridNum newSpot;
                    probabilityBoard[row][col].possibilities -= 1;
                    newSpot.row = row;
                    newSpot.col = col;
                    for (int val = 0; val < 9; val++) {
                        if (probabilityBoard[row][col].possible[val] == true) {
                            cout << val + 1 << endl;
                            probabilityBoard[row][col].num = val + 1;
                            newSpot.num = val + 1;
                        }
                    }
                    cout << "newSpot.row " <<  newSpot.row;
                    cout << " newSpot.col " << newSpot.col;
                    cout << " newSpot.num " << newSpot.num << endl;
                    cout << "removed row" << endl;
                    removeRow(probabilityBoard, newSpot, output);
                    cout << "removed col" << endl;
                    removeCol(probabilityBoard, newSpot, output);
                    cout << "removed square" << endl;
                    removeSquare(probabilityBoard, newSpot, output);
                    known.push(newSpot);
                    totalKnown += 1;
                    if (output) {
                        outputQueue->push(newSpot);
                    }
                }
            }
        }
    }
}

bool HumanHeuristic::getAvailable(posInfo (&probabilityBoard)[9][9]) {
    for (int choose = 2; choose < 9; choose++) {
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                pair<int, int> thisPos;
                if (!memo[row][col] && probabilityBoard[row][col].possibilities == choose) {
                    gridNum checkNum;
                    checkNum.row = row;
                    checkNum.col = col;
                    for (int val = 0; val < 9; val++) {
                        if (probabilityBoard[row][col].possible[val] == true) {
                            probabilityBoard[row][col].num = val + 1;
                            checkNum.num = val + 1;
                            cout << "checkNum row " << checkNum.row;
                            cout << " checkNum col " << checkNum.col;
                            cout << " checkNum num " << checkNum.num << endl;
                            memo[row][col] = true;
                            recursion.push(checkNum);
                        }
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

bool HumanHeuristic::solveHeuristically(gridArr board, bool output, int curTotal) {
    totalKnown = curTotal;
    currentRecurseStack = 0;
    posInfo probabilityBoard[9][9];  // 81 total squares.
    setboard(board, probabilityBoard);
    while (known.size() != 0) {
        cout << "in while loop" << endl;
        gridNum currentSpot = known.top();
        known.pop();
        cout << "removed row" << endl;
        removeRow(probabilityBoard, currentSpot, output);
        cout << "removed col" << endl;
        removeCol(probabilityBoard, currentSpot, output);
        cout << "removed square" << endl;
        removeSquare(probabilityBoard, currentSpot, output);
    }
    // If all of the squares are filled then we are done.
    cout << "done while loop" << endl;
    cout << "total known " << totalKnown << endl;
    if (totalKnown == 81) {
        return true;
    } else {
        cout << "in recursion" << endl;
        cout << "after if" << endl;
        getAvailable(probabilityBoard);
        cout << "available" << endl;
        // Calculate the new board to pass in to recursively solve now.
        gridArr newBoard;
        for (int row = 0; row < 9; row++) {
            for (int col = 0; col < 9; col++) {
                newBoard[row][col] = probabilityBoard[row][col].num;
            }
        }
        while (recursion.size() != 0) {
            cout << "recursing" << endl;
            cout << endl;
            gridNum tryNum = recursion.top();
            recursion.pop();
            newBoard[tryNum.row][tryNum.col] = tryNum.num;
            int prevTotal = totalKnown;
            if (solveHeuristically(newBoard, output, prevTotal)) {
                cout << "returned true" << endl;
                return true;
            }
        }
    }

    // Need to fix recursion. use memoisation? need to reset probabilities
    // totalKnown is seemingly being carried over instead of being reset.
    return false;
}
