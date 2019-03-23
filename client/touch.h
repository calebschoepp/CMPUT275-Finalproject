#ifndef TOUCH_H
#define TOUCH_H

#include "consts_and_types.h"

#include <TouchScreen.h>

class Touch {
public:
    // Returns which button was pressed
    button readButtons();

private:
    TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

};

#endif