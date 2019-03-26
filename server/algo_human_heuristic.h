#ifndef ALGO__HUMAN_HEURISTIC_H
#define ALGO__HUMAN_HEURISTIC_H

#include <queue>
#include <array>
#include <utility>

using namespace std;

// Constants and definitions
#define FULL make_pair(-1, -1)
typedef array<array<int, 9>, 9> gridArr;
struct gridNum {
    int row;
    int col;
    int num;
};
struct posInfo {
    int num = 0;
    int possibilities = 9;
    bool possible[9] = {true};
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
    bool getAvailable(posInfo (&probabilityBoard)[9][9], queue<gridNum> &possibleNums);
    bool solveHeuristically(gridArr board, bool output);

    queue<gridNum> known;
    int totalKnown;
};

#endif
