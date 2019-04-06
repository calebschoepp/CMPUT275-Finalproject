/*
Names: Robert Mah, Caleb Schoepp
ID: 1532565, 1534577
CCID: rjmah1, cwschoep
CMPUT 275 , Winter 2019

Arduino Sudoku Solver
*/


#ifndef ALGO_DANCING_LINKS_H
#define ALGO_DANCING_LINKS_H

#include <queue>
#include <array>
#include <vector>
#include <math.h>
#include "consts_and_types.h"

#define COLS 324  // constraints
#define ROWS 729  // ways to place numbers

struct Node {
    Node *left;
    Node *right;
    Node *up;
    Node *down;
    Node *col;
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
    // Member variables
    std::queue<gridNum> *outputQueue;
    gridArr board;
    bool problemMatrix[ROWS + 1][COLS];
    Node matrix[ROWS + 1][COLS];
    Node *root;
    vector<Node*> solution;
    Node *rowHeader[ROWS + 1];
    bool finished;

    inline int rowFromMatrixRow(Node *row);
    inline int colFromMatrixRow(Node *row);
    inline int numFromMatrixRow(Node *row);
    void popFromSolution();
    void pushToSolution(Node *row);
    void addBoardToMatrix();
    void addRowToSolution(Node *row);
    void buildProblemMatrix();
    void buildMatrix();
    void cover(Node *target);
    void uncover(Node *target);
    void search(int k);
    Node * minColumn();
    void printSolutions();
    int getRight(int i );
    int getLeft(int i );
    int getUp(int i );
    int getDown(int i );
    inline int getRowIndex(int row, int col, int num);

};

#endif
