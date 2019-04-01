#ifndef ALGO_BACKTRACKING_H
#define ALGO_BACKTRACKING_H

#include <queue>
#include <array>
#include <utility>
#include "consts_and_types.h"

class Backtracking {
public:
    // Constructors and deconstructors
    Backtracking(std::queue<gridNum> *displayQueue,
        gridArr boardCopy);

    // Primary interface
    void solve();
    bool checkSolvability();

private:
    gridArr board;
    std::queue<gridNum> *outputQueue;

    // Main recursive DFS solver
    bool solveRecur(gridArr board, bool output);

    // Validity check helpers
    bool cellPermitted(const gridArr &board, int row, int col, int num);
    bool rowPermitted(const gridArr &board, int row, int num);
    bool colPermitted(const gridArr &board, int col, int num);
    bool squarePermitted(const gridArr &board, int realRow, int realCol, int num);

    // Return pair holding new cell location
    std::pair<int, int> newLocation(gridArr board);
};

#endif
