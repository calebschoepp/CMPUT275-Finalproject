/*
  VERY IMPORTANT
  the struct shared_vars contains all of the variables that are
  "global" to the project across multiple files.

  In particular, you are mostly concerned with
   - shared.num_waypoints: the number of waypoints on the path
   - shared.waypoints[]: the lat/lon pairs of these waypoints
   - max_waypoints (a global const, not in the shared_vars struct):
     the maximum number of waypoints that can be stored in the
     shared.waypoints[] array
*/

#ifndef __CONSTS_AND_TYPES_H
#define __CONSTS_AND_TYPES_H

#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include "lcd_image.h"


Adafruit_ILI9341* tft;


// collect all pins in a namespace
namespace clientpins {
    // Pins and for the zoom in and out buttons.
    const uint8_t zoom_in_pin = 2;
    const uint8_t zoom_out_pin = 3;

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

    // dimensions of the bottom "display" that has the FROM? or TO? prompt
    const int16_t msg_width = tft_width;
    const int16_t msg_height = 24;

    // the display window size for the map of edmonton
    const int16_t display_width = tft_width;
    const int16_t display_height = tft_height - msg_height;
};

#endif
