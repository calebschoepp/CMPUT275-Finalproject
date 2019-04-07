/*
Names: Robert Mah, Caleb Schoepp
ID: 1532565, 1534577
CCID: rjmah1, cwschoep
CMPUT 275 , Winter 2019

Arduino Sudoku Solver
*/

#ifndef ALGO_IMPROVED_HUMAN_HEURISTIC_H
#define ALGO_IMPROVED_HUMAN_HEURISTIC_H

// currently only works with "easy" sudokus
#include <queue>
#include <array>
#include <utility>
#include <stack>
#include <unordered_set>
#include "consts_and_types.h"

using namespace std;

class ImprovedHumanHeuristic {
public:
    // Constructors and deconstructors
    ImprovedHumanHeuristic(queue<gridNum> *displayQueue, gridArr boardCopy);

    // Primary interface
    void solve();
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
    gridArr setNewBoard(posInfo (&probBoard)[9][9]);
    bool solveHeuristically(gridArr board, bool output);
};

#endif
