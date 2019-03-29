#include "algo_dancing_links.h"

#include <iostream>

DancingLinks::DancingLinks(std::queue<gridNum> *displayQueue,
        gridArr boardCopy) {
    board = boardCopy;
    outputQueue = displayQueue;
    buildProblemMatrix();

}

void buildProblemMatrix() {
    
}

void DancingLinks::solve() {
    // Wrapper for public access
}

bool DancingLinks::checkSolvability() {
    // Wrapper to see if given board is solvable
}

void DancingLinks::cover(Node *target) {

}

void DancingLinks::uncover(Node *target) {

}

void DancingLinks::search(int k) {

}

Node * DancingLinks::minColumn() {

}

int DancingLinks::getRight(int i) {
    if (i-1 < 0) {
        return COLS - 1;
    } else {
        return i - 1;
    }
}

int DancingLinks::getLeft(int i) {
    return (i+1) % COLS;
}

int DancingLinks::getUp(int i) {
    if (i-1 < 0) {
        return ROWS - 1;
    } else {
        return i - 1;
    }
}

int DancingLinks::getDown(int i) {
    return (i+1) % ROWS;
}