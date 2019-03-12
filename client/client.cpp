/*

All of the primary functionality will live in here
For now I think we should just keep this as a script and not a class
If it snowballs out of control in complexity and state management becomes
a pain then we can maybe make this a class and have a simple runner script.

Clients job is to take in input from the serial-mon and tft touchscreen, and translate
this into responses for the server through serial-mon and visual outputs on the screen.

It will exsist in a number of states. These could include:
- Main menu
- Settings menu
- Try it screen
- Solving (communicating with server/no touch input)
- Checking (communicating with server/no touch input)
- Solved
- Etc.

It will transition between states based on touch input or serial response

? Each state will be a function and will have its own tight loop taking in the proper input,
providing the proper output, and calling the next state function as necessary ?

*/


// Just some test stuff
#include "consts_and_types.h"

using namespace std;

void fillSquare(int gridx, int gridy) {
    int x = 6 + 24 * gridx;
    int y = 4 + 26 * gridy;
    tft.fillRect(x, y, 23, 25, ILI9341_LIGHTGREY);
}

void fillNum(int gridx, int gridy, int num) {
    int x = 6 + 4 + 24 * gridx;
    int y = 4 + 2 + 26 * gridy;
    tft.setCursor(x, y);
    tft.setTextSize(3);
    tft.print(num);
}

int main() {
    init();
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(ILI9341_WHITE);
    tft.setTextColor(ILI9341_BLACK);
    tft.setTextSize(3);

    int x = 10; // 9
    int y = 6; // 5

    // Print numbers
    for (int i = 0; i < 9; ++i) {
        for (int j = 1; j < 10; ++j) {
            tft.setCursor(x, y);
            x += 24;
            tft.print(j);

        }
        x = 10;
        y += 26;
    }

    // Print gridlines
    x = 5;
    y = 3;
    // Horizontal
    for (int i = 0; i < 10; ++i) {
        tft.drawLine(x, y, x + 216, y, ILI9341_BLACK);
        y += 26;
    }
    x = 5;
    y = 3;
    // Vertical
    for (int i = 0; i < 10; ++i) {
        tft.drawLine(x, y, x, y + 234, ILI9341_BLACK);
        x += 24;
    }

    // Draw buttons
    tft.fillRect(229, 5, 86, 73, ILI9341_GREEN);
    tft.fillRect(229, 83, 86, 73, ILI9341_RED);
    tft.fillRect(229, 161, 86, 73, ILI9341_BLUE);
    tft.setCursor(229 + 20, 30 + 5);
    tft.setTextSize(2);
    tft.print("MAKE");
    tft.setCursor(229 + 20, 30 + 5 + 78 );
    tft.print("STOP");
    tft.setCursor(229 + 20, 30 + 5 + 78 + 78);
    tft.print("BACK");

    // Fill square testing
    fillSquare(1, 1);
    fillSquare(6, 8);
    fillNum(1, 1, 3);
    fillSquare(6, 6);
    fillNum(6, 6, 7);
    return 0;
}