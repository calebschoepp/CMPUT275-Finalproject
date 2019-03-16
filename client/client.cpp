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

#include <Arduino.h>

#include "render.h"
#include "touch.h"
#include "joy.h"
#include "serial_comm.h"
#include "consts_and_types.h"

using namespace std;

// Globally shared state variables
shared_vars shared;

void setup() {
    // Initialize the Arduino
    init();
}

state main_menu() {
    // Draw board
    // Draw buttons
    while (true) {
        // Take in touch input
        button touchInput = touch.readButtons();
        if (touchInput == button::TOP) {
            return state::SOLVE;
        } else if (touchInput == button::MIDDLE) {
            return state::TRY_IT;
        } else if (touchInput == button::BOTTOM) {
            return state::SETTINGS;
        }
    }
}

state settings() {
    // Draw board
    // Draw buttons
    while (true) {
        // Take in touch input
        button touchInput = touch.readButtons();
        if (touchInput == button::TOP) {
            // Iterate to next algorithm
            shared.algorithm++;
            // Redraw the button

        } else if (touchInput == button::MIDDLE) {
            // Iterate to the next board
            shared.board++;
            // Redraw the button

            // Redraw the board

        } else if (touchInput == button::BOTTOM) {
            return state::MAIN_MENU;
        }
    }
}

state solve() {
    // Draw board
    // Draw button
    // Draw start of messaging area

    // Serially communicate with server to start solving
    // Display time that solving took

    // Load in series of changes into an array through serial comms
    // Display time that loading took

    for (elements in array)) {
        // Display new change onto board
        /
    }
    // Display how long displaying took

    while (true) {
        // Take in touch input
        button touchInput = touch.readButtons();
        if (touchInput == button::BOTTOM) {
            return state::MAIN_MENU;
        }
    }
}

state try_it() {
    // Draw board
    // Draw button
    // Draw start of messaging area

    while(true) {
        // Take in touch input
        button touchInput = touch.readButtons();
        if (touchInput == button::BOTTOM) {
            return state::MAIN_MENU;
        }

        // Take in joystick input
        if (joy.joyPressed()) {
            // Cycle number displayed in current square
            // TODO
            continue;
        }
        direction joyInput = joy.joyMoved();
        // joystick pressed -> cycle number in square and continue while loop
        // joystick moved -> move selected square and run check
            // Check serially communicates with server to see if it is right

        // If the board is full and it can be solved then display solved
    }
}

int main() {
    // Setup the arduino
    setup();

    // Build the Arduino interfacing objets
    Render render = Render();
    SerialComm serial_comm = SerialComm();
    Touch touch = Touch();
    Joy joy = Joy();

    // Start at the main menu when arduino is turned on or reset
    state curr_state = MAIN_MENU;

    // Infinite loop finite state machine that client will always live in
    while (true) {
        // curr_state will change after each state based on return
        switch (curr_state) {
            case state::MAIN_MENU:
                curr_state = main_menu();
                break;

            case state::SETTINGS:
                curr_state = settings();
                break;

            case state::SOLVE:
                curr_state = solve();
                break;

            case state::TRY_IT:
                curr_state = try_it();
                break;
        
            default:
                break;
        }
    }
    return 0;
}