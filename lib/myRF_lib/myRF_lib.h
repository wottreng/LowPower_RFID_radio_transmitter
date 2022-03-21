#pragma once

#include <Arduino.h>
//#include <string.h>

class myRF_lib_c {
public:
    void init();
    //void loop();
    void send_message();
    //void wakeUp();

};

extern myRF_lib_c myRF_lib;
