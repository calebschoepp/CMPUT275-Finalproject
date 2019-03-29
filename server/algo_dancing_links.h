#ifndef ALGO_DANCING_LINKS_H
#define ALGO_DANCING_LINKS_H

#include <queue>
#include <array>
#include <utility>

// Constants and definitions
#define FULL std::make_pair(-1, -1)
typedef std::array<std::array<int, 9>, 9> gridArr;
struct gridNum {
    int row;
    int col;
    int num;
};

class DancingLinks {
public:
    // Constructor
    DancingLinks(std::queue<gridNum> *displayQueue,
        gridArr boardCopy);

    // Primary interface
    void solve();
    bool checkSolvability();

private:
    gridArr board;
    std::queue<gridNum> *outputQueue;

    
};

#endif
