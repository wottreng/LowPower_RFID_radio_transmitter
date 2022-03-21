#pragma once

#include <Arduino.h>

#define lowPower_mode true // use low power mode

class myLowPower_c {
public:
    void init();
    void loop();
    void sleep_500MS();
    void sleep_120MS();
};

extern myLowPower_c myLowPower;