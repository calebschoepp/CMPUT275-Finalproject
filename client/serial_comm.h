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
    selectAlgo();
    selectBoard(point_change changes[81]);
    solve();
    solvedSize();

private:

};

#endif
