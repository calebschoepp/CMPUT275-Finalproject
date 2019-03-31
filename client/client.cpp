/*

All of the primary functionality will live in here
For now I think we should just keep this as a script and not a class
If it snowballs out of control in complexity and state management becomes
a pain then we can maybe make this a class and have a simple runner script.

Clients job is to take in input from the serial-mon and tft touchscreen, and translate
this into responses for the server through serial-mon and visual outputs on the screen.

It will exsist in a number of states. These could include:
- Main menu
- Setup menu
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

// Arduino interfacing objets
Render *render;
SerialComm *serial_comm;
Touch *touch;
Joy *joy;

void setup() {
    // Initialize the Arduino
    init();

    // Hardware pin pullups
    pinMode(JOY_SEL, INPUT_PULLUP);

    // Instantiate interface objects
    render = new Render();
    serial_comm = new SerialComm();
    touch = new Touch();
    joy = new Joy();

}

state main_menu() {
    // Draw board
    if (shared.redraw_board) {
        render->drawBoard();
        shared.redraw_board = false;
    }
    // Draw buttons
    render->cleanButtonArea();
    render->drawButton(TOP, "SOLVE", ILI9341_GREEN);
    render->drawButton(MIDDLE, "TRY IT", ILI9341_ORANGE);
    render->drawButton(BOTTOM, "SETUP", ILI9341_PINK);

    while (true) {
        // Take in touch input
        button touchInput = touch->readButtons();
        if (touchInput == TOP) {
            return SOLVE;
        } else if (touchInput == MIDDLE) {
            return TRY_IT;
        } else if (touchInput == BOTTOM) {
            return SETUP;
        }
    }
}

state settings() {
    // Draw board
    if (shared.redraw_board) {
        render->drawBoard();
        shared.redraw_board = false;
    }
    // Draw buttons
    render->cleanButtonArea();
    render->drawButton(TOP, "ALGO", ILI9341_YELLOW);
    render->drawButton(MIDDLE, "BOARD", ILI9341_CYAN);
    render->drawButton(BOTTOM, "BACK", ILI9341_RED);

    while (true) {
        // Take in touch input
        button touchInput = touch->readButtons();
        if (touchInput == TOP) {
            // Iterate to next algorithm
            ++shared.algorithm;
            // Redraw the button
            render->drawButton(TOP, "ALGO", ILI9341_YELLOW);
            // Update server algo
            serial_comm->selectAlgo();
            delay(250);


        } else if (touchInput == MIDDLE) {
            // Iterate to the next board
            ++shared._board_type;
            // Redraw the button
            render->drawButton(MIDDLE, "BOARD", ILI9341_CYAN);
            // Update server board type
            point_change changes[81];
            serial_comm->selectBoard(changes);

            // Update board


            delay(250);

            // Redraw the board
            render->drawBoard();

        } else if (touchInput == BOTTOM) {
            return MAIN_MENU;
        }
    }
}

state solve() {
    // Draw board
    if (shared.redraw_board) {
        render->drawBoard();
        shared.redraw_board = false;
    }
    // Draw button
    render->cleanButtonArea();
    render->drawButton(BOTTOM, "BACK", ILI9341_RED);

    // Draw start of messaging area
    render->textBox();

    while (true) {
        bool communication = true;
        // Serially communicate with server to start solving
        long int time = serial_comm->solve();

        // Display time that solving took


        long int disp_size = serial_comm->solvedSize();
        point_change change

        for (int change = 0; change < disp_size; ++change) {
            bool breakout = serial_comm->getChange(change);

            if (breakout) {
                communication = false;
                break;
            }

            // Display the change

        }
        if (communication) {
            break;
        }
    }

    shared.redraw_board = true;

    while (true) {
        // Take in touch input
        button touchInput = touch->readButtons();
        if (touchInput == BOTTOM) {
            return MAIN_MENU;
        }
    }
}

state try_it() {
    // Draw board
    if (shared.redraw_board) {
        render->drawBoard();
        shared.redraw_board = false;
    }
    // Draw button
    render->cleanButtonArea();
    render->drawButton(BOTTOM, "BACK", ILI9341_RED);

    // Draw start of messaging area
    render->textBox();

    // Vars for user entry
    int num_to_enter = 0;
    int sel_x = 0;
    int sel_y = 0;


    ///////////////// bool yes serial_comm->checkSolvability(point_change change);

    render->select(sel_x, sel_y, ILI9341_RED);

    while(true) {
        // Take in touch input
        button touchInput = touch->readButtons();
        if (touchInput == BOTTOM) {
            shared.redraw_board = true;
            return MAIN_MENU;
        }

        // Take in joystick input
        if (joy->joyPressed()) {
            // Cycle number displayed in current square
            if (shared.board[sel_x][sel_y] == 0) {
                num_to_enter += 1;
                num_to_enter %= 10;
                render->fillNum(sel_x, sel_y, num_to_enter, ILI9341_BLUE);
                shared.board_input[sel_x][sel_y] = num_to_enter;
                delay(150);
            }
            continue;
        }
        direction joyInput = joy->joyMoved();

        if (joyInput != NONE_D) {
            // Deselect
            render->select(sel_x, sel_y, ILI9341_WHITE);
        }

        if (joyInput == UP) {
            sel_y -= 1;
            sel_y = constrain(sel_y, 0, 8);
        } else if (joyInput == DOWN) {
            sel_y += 1;
            sel_y = constrain(sel_y, 0, 8);
        } else if (joyInput == LEFT) {
            sel_x -= 1;
            sel_x = constrain(sel_x, 0, 8);
        } else if (joyInput == RIGHT) {
            sel_x += 1;
            sel_x = constrain(sel_x, 0, 8);
        }

        if (joyInput != NONE_D) {
            // Reselect
            render->select(sel_x, sel_y, ILI9341_RED);
            num_to_enter = shared.board_input[sel_x][sel_y];
            delay(250);

            // Check solvability
            // TODO
            // serial_comm->
        }

        // If the board is full and it can be solved then display solved
        // TODO
    }
}

int main() {
    // Setup the arduino
    setup();

    // Start at the main menu when arduino is turned on or reset
    state curr_state = MAIN_MENU;

    // Initial shared states
    shared.redraw_board = true;
    shared._board_type = EASY_00;
    shared.algorithm = BACKTRACKING;

    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            shared.board[i][j] = 0;
        }
    }

    shared.board[1][5] = 3;

    /// TEST
    // render->drawBoard();
    // render->drawGrid();
    // render->fillNum(0, 0, 5, ILI9341_BLACK);
    // render->fillNum(1,1,3, ILI9341_BLACK);
    // render->fillNum(0, 8, 4, ILI9341_BLACK);
    // render->fillNum(3, 8, 7, ILI9341_BLACK);
    // render->fillNum(5, 2, 8, ILI9341_BLACK);
    // render->fillNum(6, 6, 9, ILI9341_BLACK);
    // render->select(0, 0, ILI9341_RED);
    // render->select(3, 5, ILI9341_RED);
    // render->select(6, 6, ILI9341_RED);
    // render->select(7, 7, ILI9341_RED);
    // // render->drawButton(TOP, ILI9341_GREEN);
    // // render->drawButton(MIDDLE, ILI9341_BLUE);
    // render->drawButton(BOTTOM, ILI9341_RED);
    // render->textBox();




    // Infinite loop finite state machine that client will always live in
    while (true) {
        // curr_state will change after each state based on return
        switch (curr_state) {
            case MAIN_MENU:
                curr_state = main_menu();
                break;

            case SETUP:
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
