#ifndef __CONSTS_AND_TYPES_H
#define __CONSTS_AND_TYPES_H

#include <Arduino.h>

// Touch screen pins
#define YP A2
#define XM A3
#define YM 5
#define XP 4

// Different states for the FSM
enum class state {MAIN_MENU, SETTINGS, SOLVE, TRY_IT};

// Different button spots
enum class button {TOP, MIDDLE, BOTTOM, NONE};

// Different joystick directions
enum class direction {UP, DOWN, LEFT, RIGHT, NONE};

// Algorithm choices
enum class algo {BACKTRACKING, END_OF_ALGO};

// ++ overloading for algo to iterate through it
inline algo& operator++(algo &a) {
  a = static_cast<algo>(static_cast<int>(a) + 1);
  if (a == algo::END_OF_ALGO)
    a = algo::BACKTRACKING;
  return a;
}

// Board choices
enum class board_type {EASY_00, MED_00, HARD_00, END_OF_BOARD};

// ++ overloading for board to iterate through it
inline board_type& operator++(board_type &a) {
  a = static_cast<board_type>(static_cast<int>(a) + 1);
  if (a == board_type::END_OF_BOARD)
    a = board_type::EASY_00;
  return a;
}

struct shared_vars {
    // Algorithm to be used in solve menu
    algo algorithm;

    // Current board type
    board_type _board_type;

    // Whether or not to redraw board on entry into new state
    bool redraw_board;

    // Current board but number representation [x][y]
    int board[9][9];
};

// collect all pins in a namespace
namespace clientpins {

    // the pins used to connect to the AdaFruit display
    const uint8_t sd_cs = 6;
    const uint8_t tft_cs = 10;
    const uint8_t tft_dc = 9;

    // analog pins for joystick axes
    const uint8_t joy_x_pin = A1;
    const uint8_t joy_y_pin = A0;

    // joystick button pin
    const uint8_t joy_button_pin = 8;
}

// constants related to the display
namespace displayconsts {
    // physical dimensions of the tft display
    const int16_t tft_width = 320;
    const int16_t tft_height = 240;
};

// constants related to the touchcreen
namespace touchconsts {
    // Calibration data for the touch screen, obtained from documentation.
    // The minimum/maximum possible readings from the touch point.
    const int TS_MINX = 150;
    const int TS_MINY = 120;
    const int TS_MAXX = 920;
    const int TS_MAXY = 940;

    // Thresholds to determine if there was a touch.
    const int MINPRESSURE = 10;
    const int MAXPRESSURE = 1000;
}

// constants related to joystick
namespace joyconsts {
    #define JOY_VERT  A1 // should connect A1 to pin VRx.
    #define JOY_HORIZ A0 // should connect A0 to pin VRy.
    #define JOY_SEL   8
    #define JOY_CENTER   512
    #define JOY_DEADZONE 64
}

// Constants for drawing to arduino
namespace renderconsts {
    const int cell_width = 24;
    const int cell_height = 26;
    const int border_pad = 3;
    const int num_lines = 10;
    const int num_cells = 9;
    const int button_width = 91;
    const int button_height = 76;
    const int button_start_x = 226;
}

#endif
