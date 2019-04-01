#include "algo_dancing_links.h"

#include <iostream>

DancingLinks::DancingLinks(std::queue<gridNum> *displayQueue, gridArr boardCopy) {
    board = boardCopy;
    outputQueue = displayQueue;
    root = new Node();
    buildProblemMatrix();
    buildMatrix();
}

void DancingLinks::buildProblemMatrix() {
    cout << "Building prob matrix" << endl;
    // Pre-initalize to false
    for (int i = 0; i < ROWS + 1; ++i) {
        for (int j = 0; j < COLS; ++j) {
            problemMatrix[i][j] = false;
        }
    }
    // Make first row all true to make col headers
    for (int i = 0; i < COLS; ++i) {
        problemMatrix[0][i] = true;
    }
    // Build the rest of the problem matrix by using know sudoku constraints and options
    int r = 1;
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            for (int num = 1; num < 10; ++num) {
                int j;
                // Constraint: Number in each cell
                j = ((row) * 9) + col;
                problemMatrix[r][j] = true;

                // Constraint: 1-9 in each row
                j = ((row) * 9) + num - 1 + 81;
                problemMatrix[r][j] = true;

                // Constraint: 1-9 in each col
                j = ((col) * 9) + num - 1 + 162;
                problemMatrix[r][j] = true;

                // Constraint: 1-9 in each square
                j = num - 1 + 243 + (9 * floor(col/3)) + (27 * floor(row/3));
                // j = 9 * (3 * (floor(col/3) + 1)) + (3 * (floor(row/3) + 1)) + num - 1 + 243;
                problemMatrix[r][j] = true;

                r++;
            }
        }
    }
    cout << "Done building prob matrix" << endl;
}

void DancingLinks::buildMatrix() {
    cout << "Building matrix" << endl;
    // Build the matrix
    for (int row = 0; row < ROWS + 1; ++row) {
        for (int col = 0; col < COLS; ++col) {
            // Build nodes only where problem matrix specifies
            if (this->problemMatrix[row][col]) {
                // Increase node count of column header
                // matrix[0][col].nodeCount += 1;

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
                } while (scol != col && !problemMatrix[srow][scol]);
                matrix[row][col].right = &matrix[srow][scol];

                // Left pointer
                srow = row;
                scol = col;
                do {
                    scol = getLeft(scol);
                } while (scol != col && !problemMatrix[srow][scol]);
                matrix[row][col].left = &matrix[srow][scol];

                // Up pointer
                srow = row;
                scol = col;
                do {
                    srow = getUp(srow);
                } while (srow != row && !problemMatrix[srow][scol]);
                matrix[row][col].up = &matrix[srow][scol];

                // Down pointer
                srow = row;
                scol = col;
                do {
                    srow = getDown(srow);
                } while (srow != row && !problemMatrix[srow][scol]);
                matrix[row][col].down = &matrix[srow][scol];
            }
        }
    }

    // Count ones for header column
    for (Node *col = &matrix[0][0]; col != &matrix[0][0]; col = col->right) {
        for (Node *row = col->down; row != col; row = row->down) {
            col->nodeCount++;
        }
    }

    // Link root of matrix to matrix
    root->right = &matrix[0][0];
    root->left = &matrix[0][COLS - 1];

    matrix[0][0].left = root;
    matrix[0][COLS - 1].right = root;
    cout << "Done building matrix" << endl;
}

void DancingLinks::solve() {
    // Wrapper for public access
    search(0);
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
    if (root->right == root) {
        // TODO
        printSolutions();
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

void DancingLinks::printSolutions() {
    for (auto itr = solution.begin(); itr != solution.end(); itr++) {
        cout << (*itr)->rowID << " " << (*itr)->colID;
    }
    cout << endl;
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