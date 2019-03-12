#ifndef __CONSTS_AND_TYPES_H
#define __CONSTS_AND_TYPES_H

#include <Arduino.h>
#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>
#include <TouchScreen.h>
#include "lcd_image.h"

#define TFT_DC 9
#define TFT_CS 10

// Touch screen pins
#define YP A2
#define XM A3
#define YM 5
#define XP 4

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);


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
};

// constants related to the touchcreen
namespace touchconsts {
  // Calibration data for the touch screen, obtained from documentation.
  // The minimum/maximum possible readings from the touch point.
  #define TS_MINX 150
  #define TS_MINY 120
  #define TS_MAXX 920
  #define TS_MAXY 940

  // Thresholds to determine if there was a touch.
  #define MINPRESSURE   10
  #define MAXPRESSURE 1000
}

#endif
