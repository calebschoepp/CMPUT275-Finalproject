#include "algo_dancing_links.h"

#include <iostream>

DancingLinks::DancingLinks(std::queue<gridNum> *displayQueue,
        gridArr boardCopy) {
    board = boardCopy;
    outputQueue = displayQueue;
    buildProblemMatrix();

}

void DancingLinks::buildProblemMatrix() {
    
}

void DancingLinks::buildMatrix() {
    // Column headers
    for (int col = 0; col < COLS; ++col) {
        matrix[0][col].nodeCount = 0;
        
    }


    // Rest of matrix
    for (int row = 1; row < ROWS + 1; ++row) {
        for (int col = 0; col < COLS; ++col) {
            // Build nodes only where problem matrix specifies
            if (this->problemMatrix[row - 1][col]) {
                // Increase node count of column header
                matrix[0][col].nodeCount += 1;

                // Link node to column header
                matrix[row][col].col = &matrix[0][col];

                // ids
                matrix[row][col].rowID = row;
                matrix[row][col].colID = col;

                // Initalize search row and col vars
                int srow, scol;

                // Right pointer
                srow = row;
                scol = col;
                do {
                    scol = getRight(scol);
                } while (scol != col && !problemMatrix[srow - 1][scol]);
                matrix[row][col].right = &matrix[srow][scol];

                // Left pointer
                srow = row;
                scol = col;
                do {
                    scol = getLeft(scol);
                } while (scol != col && !problemMatrix[srow - 1][scol]);
                matrix[row][col].left = &matrix[srow][scol];

                // Up pointer
                srow = row;
                scol = col;
                do {
                    srow = getUp(srow);
                } while (srow != row && !problemMatrix[srow - 1][scol]);
                matrix[row][col].up = &matrix[srow][scol];

                // Down pointer
                srow = row;
                scol = col;
                do {
                    srow = getDown(srow);
                } while (srow != row && !problemMatrix[srow - 1][scol]);
                matrix[row][col].down = &matrix[srow][scol];
            }
        }
    }
}

void DancingLinks::solve() {
    // Wrapper for public access
}

bool DancingLinks::checkSolvability() {
    // Wrapper to see if given board is solvable
}

void DancingLinks::cover(Node *target) {
    // Pointer to nodes column header
    Node *colHeader = target->col;

    // Unlink the column header
    colHeader->right->left = colHeader->left;
    colHeader->left->right = colHeader->right;

    // Moving down the chosen constraint column
    // Remove every row that has similar 1's to that of chosen row
    for (Node *row = colHeader->down; row != colHeader; row = row->down) {
        for (Node *col = row->right; col != row; col = col->right) {
            // Unlink node from its col
            col->up->down = col->down;
            col->down->up = col-> up;

            // Decrease count of cells in specific column
            matrix[0][col->colID].nodeCount -= 1;
        }
    }
}

void DancingLinks::uncover(Node *target) {
    // Pointer to nodes column header
    Node *colHeader = target->col;

    // Moving down the chosen constraint column
    // Add every row that has similar 1's to that of chosen row, now go left
    for (Node *row = colHeader->up; row != colHeader; row = row->up) {
        for (Node *col = row->left; col != row; col = col->left) {
            // Link node from its col
            col->up->down = col;
            col->down->up = col;

            // Increase count of cells in specific column
            matrix[0][col->colID].nodeCount += 1;
        }
    }
}

void DancingLinks::search(int k) {
    // Means we are done
    if (root->right = root) {
        /// DO WHAT I NEED TODO
        return;
    }

    // Find a column to cover
    Node *col = minColumn();

    // Now we cover the column
    cover(col);

    // Now we recursively check each possible row
    for (Node *row = col->down; row != col; row = row->down) {
        solution.push_back(row);

        // Now cover all the solution overlap from the chosen row
        for (Node *overlap = row->right; overlap != row; overlap = overlap->right) {
            cover(overlap);
        }

        // Here is the recursive search
        search(k+1);

        // Undo what we did to the global data structure
        solution.pop_back();
        for (Node *deoverlap = row->left; deoverlap != row; deoverlap = deoverlap->left) {
            uncover(deoverlap);
        }

    }
    uncover(col);
}

Node * DancingLinks::minColumn() {
    Node *best = root->right;
    for (Node *test = root->right->right; test != root; test = test->right) {
        if (test->nodeCount < best->nodeCount) {
            best = test;
        }
    }
    return best;
}

inline int DancingLinks::getRight(int i) {
    if (i-1 < 0) {
        return COLS - 1;
    } else {
        return i - 1;
    }
}

inline int DancingLinks::getLeft(int i) {
    return (i+1) % COLS;
}

inline int DancingLinks::getUp(int i) {
    if (i-1 < 0) {
        return ROWS - 1;
    } else {
        return i - 1;
    }
}

inline int DancingLinks::getDown(int i) {
    return (i+1) % ROWS;
}