/*

This will be the class that will wrap all of the rendering functionality.
Anytime client needs to draw to screen it calls this class. Perhaps one public
render method correlating to each state in client.cpp. There will be one large state
containing struct it will have access to with things like current selected board, algo,
etc.

This should be very deterministic

*/

#include "render.h"

extern shared_vars shared;

Render::Render() {
    tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
    tft.begin();
    tft.setRotation(3);
}

// void Render::drawGrid() {
//     // Horizontal lines
//     int x = 5;
//     int y = 3;
//     // Vertical lines
//     for (int i = 0; i < 10; ++i) {
//         tft.drawLine();
//     }
// }