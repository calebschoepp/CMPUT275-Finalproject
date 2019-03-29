#include "algo_dancing_links.h"

#include <iostream>

DancingLinks::DancingLinks(std::queue<gridNum> *displayQueue,
        gridArr boardCopy) {
    // Constructor, copy board over
    board = boardCopy;
    outputQueue = displayQueue;
}

void DancingLinks::solve() {
    // Wrapper  for public access
}

bool DancingLinks::checkSolvability() {
    // Wrapper  to see if given board is solvable
}

