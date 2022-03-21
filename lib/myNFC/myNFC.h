#pragma once

#include <Arduino.h>
//#include <string.h>

class myNFC_c {
public:
    void init();
    bool loop();
    void power_off_reader();
    void start_rfid_reader();
};

extern myNFC_c myNFC;
