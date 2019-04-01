#ifndef ALGO__HUMAN_HEURISTIC_H
#define ALGO__HUMAN_HEURISTIC_H

#include <queue>
#include <array>
#include <utility>
#include <stack>
#include <unordered_set>
#include "consts_and_types.h"

using namespace std;

struct posInfo {
    int num = 0;
    int possibilities = 9;
    bool possible[9] = {true, true, true, true, true, true, true, true, true};
};

class HumanHeuristic {
public:
    // Constructors and deconstructors
    HumanHeuristic(queue<gridNum> *displayQueue,
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
    bool getAvailable(posInfo (&probabilityBoard)[9][9]);
    bool solveHeuristically(gridArr board, bool output, int curTotal);

    stack<gridNum> known;
    int totalKnown;
    stack<gridNum> recursion;
    int currentRecurseStack;
    stack<gridNum> currentRecurse;
    bool memo[9][9];
};

#endif
