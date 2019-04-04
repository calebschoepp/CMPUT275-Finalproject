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
    ImprovedHumanHeuristic(queue<gridNum> *displayQueue,
        gridArr boardCopy);

    // Primary interface
    void solve();
    bool checkSolvability();

private:
    gridArr board;
    queue<gridNum> *outputQueue;

    void setboard(gridArr board, posInfo (&probabilityBoard)[9][9]);
    void removeRow(posInfo (&probabilityBoard)[9][9], gridNum& currentSpot, bool output);
    void removeCol(posInfo (&probabilityBoard)[9][9], gridNum& currentSpot, bool output);
    void removeSquare(posInfo (&probabilityBoard)[9][9], gridNum& currentSpot, bool output);
    bool solveHeuristically(gridArr board, bool output, int curTotal);

    stack<gridNum> known;
    int totalKnown;

};

#endif
