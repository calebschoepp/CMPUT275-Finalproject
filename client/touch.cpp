#include "touch.h"

using namespace renderconsts;

button Touch::readButtons() {
    TSPoint touch = ts.getPoint();

    // If the touch is too soft not button registered
    if (touch.z < touchconsts::MINPRESSURE ||
        touch.z > touchconsts::MAXPRESSURE) {
        return button::NONE;
    }

    // Convert x and y to on screen coords
    int16_t x = map(touch.y, touchconsts::TS_MINY,
                       touchconsts::TS_MAXY,
                       displayconsts::tft_width - 1,
                       0);
    int16_t y = map(touch.x, touchconsts::TS_MINX,
                       touchconsts::TS_MAXX,
                       displayconsts::tft_height - 1,
                       0);     

    if (x > button_start_x) {
        if (y > 0 && y < button_height + border_pad) {
            return button::BOTTOM;
        } else if (y > button_height + border_pad && y < 2 * button_height + 2 * border_pad) {
            return button::MIDDLE;
        } else if (y > 2 * button_height + 2 * border_pad) {
            return button::TOP;
        }
    }
    return button::NONE;
}