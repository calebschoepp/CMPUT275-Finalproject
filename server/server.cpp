// includes
#include "serialport.h"
using namespace std;

int main() {
    // Simple state machine based on initial input from serial
    // Timeouts bring back to main function

    // State variables
    // int ...
    // bool ....
    SerialPort Serial("/dev/ttyACM0");
    Serial.readline(10);  // Remove any leftover bytes in the buffer.
    /*
    string state;
    state = readInState();

    switch (state) {
      case a:

      case b:

      etc.

      }


each case will call a function that then reads in the rest of the input etc.

so it  would be like server is s and client is c

c: B  // board update or something, switch statement will send it into the board update function or something similar
s: A  // Acknowledge
c: 1 3 7
s: A
*/
    return 0;
}
