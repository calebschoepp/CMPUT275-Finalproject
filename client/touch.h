#ifndef TOUCH_H
#define TOUCH_H

#include <TouchScreen.h>
#include "consts_and_types.h"

class Touch {
public:
    // Constructor
    Touch();

    // Returns which button was pressed
    button readButtons();

private:
    TouchScreen ts;

};

#endif