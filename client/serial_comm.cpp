#include "serial_comm.h"

SerialComm::SerialComm() {
    Serial.begin(9600);
    Serial.flush();
}