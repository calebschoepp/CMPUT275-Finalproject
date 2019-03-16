#include "algo_backtracking.h"
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
            cout << board[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    gridArr board = readInSudoku("./sudokus/hard-00.txt");
    queue<gridNum> changeQueue;

    Backtracking solver(&changeQueue, board);
    solver.solve();
    
    printBoard(board);

    cout << changeQueue.size() << endl;

    while (!changeQueue.empty()) {
        gridNum change = changeQueue.front();
        changeQueue.pop();
        board[change.row][change.col] = change.num;

        // cout << change.row << " " << change.col << " " << change.num << endl;

        // printBoard(board);
    }
    cout << "Done" << endl;
}