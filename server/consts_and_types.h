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

#endif
