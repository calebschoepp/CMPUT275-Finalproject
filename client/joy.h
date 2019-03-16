#ifndef JOY_H
#define JOY_H

#include "consts_and_types.h"

class Joy {
public:
    // Constructor
    Joy();
private:
    bool joyPressed();
    direction joyMoved();
};

#endif