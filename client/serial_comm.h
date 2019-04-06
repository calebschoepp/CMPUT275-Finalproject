/*
Names: Robert Mah, Caleb Schoepp
ID: 1532565, 1534577
CCID: rjmah1, cwschoep
CMPUT 275 , Winter 2019

Arduino Sudoku Solver
*/


#ifndef SERIAL_COMM_H
#define SERIAL_COMM_H

#include "consts_and_types.h"

class SerialComm {
public:
    // constructor
    SerialComm();
    // newBoard();
    // some form of communication about solvablity, probably a number of methods
    // solveCurrentBoard(displayed version);
    bool getChange(point_change *change);
    void selectAlgo();
    void selectBoard(point_change (&changes)[81]);
    long int solve();
    long int solvedSize();
    bool checkSolvability(point_change change);

private:

};

#endif
