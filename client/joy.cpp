#include "joy.h"

#include "consts_and_types.h"

bool Joy::joyPressed() {
    int read = digitalRead(JOY_SEL);
    if (read == HIGH) {
        return false;
    }
    return true;
}

direction Joy::joyMoved() {
    int xVal = analogRead(JOY_HORIZ);
    int yVal = analogRead(JOY_VERT);

    // x is inverted
    if (xVal - JOY_DEADZONE - JOY_CENTER > 0) {
        return LEFT;
    } else if((1024 - xVal) - JOY_DEADZONE - JOY_CENTER > 0) {
        return RIGHT;
    } else if (yVal - JOY_DEADZONE - JOY_CENTER > 0) {
        return DOWN;
    } else if ((1024 - yVal) - JOY_DEADZONE - JOY_CENTER > 0) {
        return UP;
    }

    return direction::NONE_D;
}