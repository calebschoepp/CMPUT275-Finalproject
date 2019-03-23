/*

This will be the class that will wrap all of the rendering functionality.
Anytime client needs to draw to screen it calls this class. Perhaps one public
render method correlating to each state in client.cpp. There will be one large state
containing struct it will have access to with things like current selected board, algo,
etc.

*/

#include "render.h"

using namespace renderconsts;

extern shared_vars shared;

Render::Render() {
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(ILI9341_WHITE);
}

void Render::reset() {
    // Draw a blank white screen
    tft.fillScreen(ILI9341_WHITE);
}

void Render::drawGrid() {
    // Horizontal lines
    int x = border_pad;
    int y = border_pad;
    for (int i = 0; i < num_lines; ++i) {
        tft.drawLine(x, y, x + (num_cells * cell_width), y, ILI9341_BLACK);
        // Thicker lines every 3
        if (i % 3 == 0) {
            tft.drawLine(x, y + 1, x + (num_cells * cell_width), y + 1, ILI9341_BLACK);
            tft.drawLine(x, y - 1, x + (num_cells * cell_width), y - 1, ILI9341_BLACK);
        }
        y += cell_height;
    }

    // Vertical lines
    x = border_pad;
    y = border_pad;
    for (int i = 0; i < num_lines; ++i) {
        tft.drawLine(x, y, x, y + (num_cells * cell_height), ILI9341_BLACK);
        // Thicker lines every 3
        if (i % 3 == 0) {
            tft.drawLine(x - 1, y, x - 1, y + (num_cells * cell_height), ILI9341_BLACK);
            tft.drawLine(x + 1, y, x + 1, y + (num_cells * cell_height), ILI9341_BLACK);
        }
        x += cell_width;
    }
}

void Render::fillNum(int gridx, int gridy, int num, uint16_t color) {
    // Grid is 0 indexed
    if (num == 0) {
        return;
    }
    // 7 is experimental value for centering text
    int x = border_pad + 7 + cell_width * gridx;
    // 6 is experimental value for centering text
    int y = border_pad + 6 + cell_height * gridy;
    tft.setCursor(x, y);
    tft.setTextSize(2);
    tft.setTextColor(color);
    tft.print(num);
}

void Render::select(int gridx, int gridy, uint16_t color) {
    // Draw a selection box in a grid cell
    int x = border_pad + 2 + cell_width * gridx;
    int y = border_pad + 2 + cell_height * gridy;
    tft.drawRect(x + 1, y + 1, cell_width - 5, cell_height - 5, color);
    tft.drawRect(x + 2, y + 2, cell_width - 7, cell_height - 7, color);
}

void Render::_button(button btn, uint16_t color) {
    // Draw a button with no text
    int x = button_start_x;
    int y;
    if (btn == button::TOP) {
        y = border_pad;
    } else if (btn == button::MIDDLE) {
        y = 2 * border_pad + button_height;
    } else if (btn == button::BOTTOM) {
        y = 3 * border_pad + 2 * button_height;
    }
    
    // Black containing rect
    tft.drawRect(x, y, button_width, button_height, ILI9341_BLACK);
    tft.drawRect(x + 1, y + 1, button_width - 2, button_height - 2, ILI9341_BLACK);
    tft.drawRect(x + 2, y + 2, button_width - 4, button_height - 4, ILI9341_BLACK);

    // Fill in color
    tft.fillRect(x + 3, y + 3, button_width - 6, button_height - 6, color);
}

void Render::buttonText(button btn, char * msg) {
    tft.setTextSize(2);
    tft.setTextColor(ILI9341_BLACK);

    // Special cases for algorithm and board
    if (msg == "ALGO") {
        switch (shared.algorithm) {
            case algo::BACKTRACKING:
                msg = "BACKTRK";
                break;
        }
    }

    if (msg == "BOARD") {
        switch (shared._board_type) {
            case board_type::EASY_00:
                msg = "EASY 00";
                break;
            case board_type::MED_00:
                msg = "MED 00";
                break;
            case board_type::HARD_00:
                msg = "HARD 00";
                break;
            case board_type::HARD_01:
                msg = "HARD 01";
                break;
            case board_type::HARD_02:
                msg = "HARD 02";
                break;
            case board_type::HARD_03:
                msg = "HARD 03";
                break;
        }
    }

    // y
    int mod = (button_height - 14) / 2;
    int y;
    if (btn == button::TOP) {
        y = border_pad + mod;
    } else if (btn == button::MIDDLE) {
        y = 2 * border_pad + button_height + mod;
    } else if (btn == button::BOTTOM) {
        y = 3 * border_pad + 2 * button_height + mod;
    }

    // x
    int x = button_start_x;
    int len = strlen(msg);
    if (len > button_max_char) {
        return;
    }
    int text_width = len * 12;
    int blank_space = button_width - text_width;
    x += blank_space / 2;
    x += 1;

    // print
    tft.setCursor(x, y);
    tft.print(msg);  
}

void Render::textBox() {
    int x = button_start_x;
    int y = border_pad;
    int height = 2 * button_height + border_pad;
    // Black containing rect
    tft.drawRect(x, y, button_width, height, ILI9341_BLACK);
    tft.drawRect(x + 1, y + 1, button_width - 2, height - 2, ILI9341_BLACK);
    tft.drawRect(x + 2, y + 2, button_width - 4, height - 4, ILI9341_BLACK);
}

void Render::drawBoard() {
    cleanGridArea();
    drawGrid();
    for (int x = 0; x < 9; ++x) {
        for (int y = 0; y < 9; ++y) {
            int num = shared.board[x][y];
            fillNum(x, y, num, ILI9341_BLACK);
        }
    }
}

void Render::cleanGridArea() {
    tft.fillRect(0, 0, 222, 240, ILI9341_WHITE);
}

void Render::drawButton(button btn, char* msg, uint16_t color) {
    _button(btn, color);
    buttonText(btn, msg);
}

void Render::cleanButtonArea() {
    tft.fillRect(222, 0, 320, 240, ILI9341_WHITE);
}

void Render::test() {
    int x = button_start_x;
    int y = border_pad + 2 + cell_height;
    tft.setCursor(x, y);
    tft.setTextSize(2);
    char* s = "SETUP";
    tft.print(s);
}