#ifndef ALGO_DANCING_LINKS_H
#define ALGO_DANCING_LINKS_H

#include <queue>
#include <array>
#include <utility>

#define COLS 324  // constraints
#define ROWS 729  // ways to place numbers

// Constants and definitions
typedef std::array<std::array<int, 9>, 9> gridArr;

struct gridNum {
    int row;
    int col;
    int num;
};

struct Node {
    Node *left;
    Node *right;
    Node *up;
    Node *down;
    int rowID;
    int colID;
    int nodeCount;
};

class DancingLinks {
public:
    // Constructor
    DancingLinks(std::queue<gridNum> *displayQueue, gridArr boardCopy);

    // Primary interface
    void solve();
    bool checkSolvability();

private:
    std::queue<gridNum> *outputQueue;
    gridArr board;
    bool problemMatrix[ROWS][COLS];

    void buildProblemMatrix();
    void cover(Node *target);
    void uncover(Node *target);
    void search(int k);
    Node * minColumn();
    int getRight(int i );
    int getLeft(int i );
    int getUp(int i );
    int getDown(int i );

};

#endif
