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
#include "render.h"
#include "touch.h"
#include "joy.h"
#include "serial_comm.h"

using namespace std;

enum state {MAIN_MENU, SETTINGS, SOLVE, TRY_IT};

void setup() {

}

state main_menu() {

}

state settings() {

}

state solve() {

}

state try_it() {

}

int main() {
    // Setup the arduino
    setup();

    // Start at the main menu when arduino is turned on or reset
    state curr_state = MAIN_MENU;

    // Infinite loop finite state machine that client will always live in
    while (true) {
        switch (curr_state) {
            case MAIN_MENU:
                curr_state = main_menu();
                break;

            case SETTINGS:
                curr_state = settings();
                break;

            case SOLVE:
                curr_state = solve();
                break;

            case TRY_IT:
                curr_state = try_it();
                break;
        
            default:
                break;
        }
    }
    return 0;
}