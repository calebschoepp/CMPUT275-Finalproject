/*

All of the primary functionality will live in here
For now I think we should just keep this as a script and not a class
If it snowballs out of control in complexity and state management becomes
a pain then we can maybe make this a class and have a simple runner script.

Clients job is to take in input from the serial-mon and tft touchscreen, and translate
this into responses for the server through serial-mon and visual outputs on the screen.

It will exsist in a number of states. These could include:
- Main menu
- Settings menu
- Try it screen
- Solving (communicating with server/no touch input)
- Checking (communicating with server/no touch input)
- Solved
- Etc.

It will transition between states based on touch input or serial response

? Each state will be a function and will have its own tight loop taking in the proper input,
providing the proper output, and calling the next state function as necessary ?

*/


// Just some test stuff
#include "consts_and_types.h"

using namespace std;

int main() {
    init();
    tft.fillScreen(ILI9431_BLACK);
    tft.print("Hello World!");
    return 0;
}