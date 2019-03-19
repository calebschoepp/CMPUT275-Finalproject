/*

This will be the class that will wrap all of the rendering functionality.
Anytime client needs to draw to screen it calls this class. Perhaps one public
render method correlating to each state in client.cpp. There will be one large state
containing struct it will have access to with things like current selected board, algo,
etc.

*/

#include "render.h"

extern shared_vars shared;

Render::Render() {
    // tft = Adafruit_ILI9341(clientpins::tft_cs, clientpins::tft_dc);
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