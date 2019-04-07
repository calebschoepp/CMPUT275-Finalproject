/*
Names: Robert Mah, Caleb Schoepp
ID: 1532565, 1534577
CCID: rjmah1, cwschoep
CMPUT 275 , Winter 2019

Arduino Sudoku Solver
*/

#ifndef ALGO_HUMAN_HEURISTIC_H
#define ALGO_HUMAN_HEURISTIC_H

#include <queue>
#include <array>
#include <utility>
#include <stack>
#include <unordered_set>
#include "consts_and_types.h"

using namespace std;

class HumanHeuristic {
public:
    // Constructors and deconstructors
    HumanHeuristic(queue<gridNum> *displayQueue, gridArr boardCopy);

    // Primary interface
    void solve();  // only works with "easy" sudokus.
    bool checkSolvability();

private:
    // Variables.
    gridArr board;
    queue<gridNum> *outputQueue;
    stack<gridNum> known;
    int totalKnown;

    // Private methods.
    void removeAll(posInfo (&probBoard)[9][9], gridNum &curSpot, bool output);
    void setboard(gridArr board, posInfo (&probBoard)[9][9]);
    void checkPos(posInfo (&probBoard)[9][9], int row, int col, bool output);
    void removeRow(posInfo (&probBoard)[9][9], gridNum& curSpot, bool output);
    void removeCol(posInfo (&probBoard)[9][9], gridNum& curSpot, bool output);
    void removeSquare(posInfo (&probBoard)[9][9], gridNum& curSpot,
            bool output);
    bool solveHeuristically(gridArr board, bool output);
};

#endif
