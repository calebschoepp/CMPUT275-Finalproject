#ifndef RENDER_H
#define RENDER_H

#include "consts_and_types.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

class Render {
public:
    // Constructor
    Render();
private:
    Adafruit_ILI9341 tft = Adafruit_ILI9341(clientpins::tft_cs, clientpins::tft_dc);
};

#endif