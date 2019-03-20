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
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(ILI9341_BLUE);
}

void Render::reset() {
    // Draw a blank white screen
    tft.fillScreen(ILI9341_WHITE);
}

void Render::drawGrid() {
    // Horizontal lines
    int x = 5;
    int y = 3;
    for (int i = 0; i < 10; ++i) {
        tft.drawLine(x, y, x + 216, y, ILI9341_BLACK);
        // Thicker lines every 3
        if (i % 3 == 0) {
            tft.drawLine(x, y + 1, x + 216, y + 1, ILI9341_BLACK);
            tft.drawLine(x, y - 1, x + 216, y - 1, ILI9341_BLACK);
        }
        y += 26;
    }

    // Vertical lines
    x = 5;
    y = 3;
    for (int i = 0; i < 10; ++i) {
        tft.drawLine(x, y, x, y + 234, ILI9341_BLACK);
        // Thicker lines every 3
        if (i % 3 == 0) {
            tft.drawLine(x, y, x, y + 234, ILI9341_BLACK);
            tft.drawLine(x + 1, y, x + 1, y + 234, ILI9341_BLACK);
        }
        x += 24;
    }
}