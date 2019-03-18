#ifndef TOUCH_H
#define TOUCH_H

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