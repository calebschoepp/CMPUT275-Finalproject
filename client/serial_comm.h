#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include "consts_and_types.h"

// Globally shared state variables
shared_vars shared;

class SerialComm {
public:
    // constructor
    SerialComm();
    // newBoard();
    // some form of communication about solvablity, probably a number of methods
    // solveCurrentBoard(displayed version);
    bool getChange(point_change change);
    void selectAlgo();
    void selectBoard(point_change changes[81]);
    void solve();
    int solvedSize();

private:

};

#endif
