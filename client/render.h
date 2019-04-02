#ifndef RENDER_H
#define RENDER_H

#include "consts_and_types.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

class Render {
public:
    // Constructor
    Render();
    void drawGrid();
    void reset();
    void clearNum(int gridx, int gridy);
    void test();
    void fillNum(int gridx, int gridy, int num, uint16_t color);
    void select(int gridx, int gridy, uint16_t color);
    void _button(button btn, uint16_t color);
    void buttonText(button btn, char* msg);
    void textBox();
    void drawBoard();
    void cleanGridArea();
    void drawButton(button btn, char* msg, uint16_t color);
    void cleanButtonArea();
    void displayTime(long int time);
    void drawSolvability(bool solvable);
    Adafruit_ILI9341 tft = Adafruit_ILI9341(clientpins::tft_cs, clientpins::tft_dc);

private:

};

#endif