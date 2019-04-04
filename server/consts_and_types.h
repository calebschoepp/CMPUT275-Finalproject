#ifndef CONSTS_AND_TYPES_H
#define CONSTS_AND_TYPES_H

#include <array>

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
    bool possible[9] = {true, true, true, true, true, true, true, true, true};
};
#endif
