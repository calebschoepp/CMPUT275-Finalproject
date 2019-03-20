#include "joy.h"

#include "consts_and_types.h"

Joy::Joy() {

}

bool Joy::joyPressed() {
    return false;
}

direction Joy::joyMoved() {
    return direction::NONE;
}