#ifndef ALGO_DFS_H
#define ALGO_DFS_H

#include <queue>
#include <tuple>
#include <array>
#include <utility>

// Constants and definitions
#define FULL std::make_pair(-1, -1)
typedef std::array<std::array<int, 9>, 9> gridArr;

class Dfs {
public:
    // Constructors and deconstructors
    Dfs(std::queue<std::tuple<int, int, int>> & displayQueue,
        gridArr board);
    ~Dfs();

    // Primary interface
    void solve();
    bool checkSolvability();

private:

    gridArr board;

    // Main recursive DFS solver
    bool solveRecur(gridArr board, bool output);

    // Validity check helpers
    bool cellPermitted(const gridArr &board, int row, int col, int num);
    bool rowPermitted(const gridArr &board, int row, int num);
    bool colPermitted(const gridArr &board, int col, int num);
    bool squarePermitted(const gridArr &board, int row_start, int col_start, int num);

    // Return pair holding new cell location
    std::pair<int, int> newLocation(gridArr board);
};

#endif