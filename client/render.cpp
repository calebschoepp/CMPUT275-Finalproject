/*

This will be the class that will wrap all of the rendering functionality.
Anytime client needs to draw to screen it calls this class. Perhaps one public
render method correlating to each state in client.cpp. There will be one large state
containing struct it will have access to with things like current selected board, algo,
etc.

This should be very deterministic

*/

#include "render.h"

#include <Adafruit_ILI9341.h>
#include <Adafruit_GFX.h>

extern 

Render::Render() {
    tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
    tft.begin();
    tft.setRotation(3);
}
