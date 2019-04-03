#include "algo_dancing_links.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

gridArr readInSudoku(string fileName) {
    gridArr board;
    fstream file;
    file.open(fileName);
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int val;
            file >> val;
            board[row][col] = val;
        }
    }
    return board;
}

void printBoard(const gridArr &board) {
    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            cout << board[col][row] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    gridArr board = readInSudoku("./sudokus/hard-00.txt");
    queue<gridNum> changeQueue;

    DancingLinks solver(&changeQueue, board);
    solver.solve();

    printBoard(board);

    cout << changeQueue.size() << endl;

    cout << endl;

    while (!changeQueue.empty()) {
        gridNum change = changeQueue.front();
        changeQueue.pop();
        board[change.col][change.row] = change.num;

        cout << change.row << " " << change.col << " " << change.num << endl;
    }
    cout << endl;
    printBoard(board);
    cout << "Done" << endl;
}
