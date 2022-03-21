#include <Arduino.h>
#include <string.h>
//
#include <myConfig.h>
#include <myLowPower.h>
#include <myNFC.h>
#include <myRF_lib.h>
//
// extern const bool debug = true;
// -----------
void setup()
{
#ifdef debug
    Serial.begin(9600); // does not work with slower clock speed
    Serial.println(F("start setup"));
#endif
    myRF_lib.init(); // for 315Mhz radio transmitter
    myNFC.init(); // for mfrc522
#ifdef lowPower_mode
    myLowPower.init(); // switch pin
#endif
//
#ifdef debug
    Serial.println(F("end setup, enter main loop"));
    Serial.flush();
#endif
    pinMode(9, OUTPUT); // onboard LED
}
// ------------
void loop()
{
    digitalWrite(9, 0);
// attach interrupt and go to sleep
#ifdef lowPower_mode
#ifdef debug
    Serial.println(F("[*] going to sleep"));
    Serial.flush();
#endif
    myLowPower.loop();
#endif
#ifdef debug
#ifdef lowPower_mode
    Serial.begin(9600); // needed when using lowPower sleep, need to reinitialize serial
#endif
    Serial.println(F("start loop"));
    Serial.flush();
#endif
    //
    digitalWrite(9, 1);
    myNFC.start_rfid_reader();
    unsigned long current_time = millis();
    while (millis() - current_time < reader_on_time) {
        // wakeup nfc for reading tag
        bool auth_status = myNFC.loop();
        // if tag is read and passwd matches, send signal to garage
        if (auth_status == true) {
            myRF_lib.send_message();
            break;
        }
    }
    //
    myNFC.power_off_reader();
#ifdef debug
    Serial.println(F("end loop"));
    Serial.flush();
#endif
#ifndef lowPower_mode
#ifdef debug
    Serial.println(F("slow down loop, lowPower mode not used"));
    Serial.flush();
#endif
    delay(500); // if lowPower mode not used then slow down loop
#endif
}
