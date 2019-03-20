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
enum class board {EASY_00, MED_00, HARD_00, END_OF_BOARD};

// ++ overloading for board to iterate through it
inline board& operator++(board &a) {
  a = static_cast<board>(static_cast<int>(a) + 1);
  if (a == board::END_OF_BOARD)
    a = board::EASY_00;
  return a;
}

struct shared_vars {
    // Algorithm to be used in solve menu
    algo algorithm;

    // Current board
    board board_type;
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

#endif
