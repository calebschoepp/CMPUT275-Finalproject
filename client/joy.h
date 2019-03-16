#ifndef JOY_H
#define JOY_H

class Joy {
public:
    // Constructor
    Joy();
private:
    bool joyPressed();
    direction joyMoved();
};

#endif