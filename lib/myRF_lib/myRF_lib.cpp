#include <Arduino.h>
//#include <string.h>
#include <RH_ASK.h> // Include RadioHead Amplitude Shift Keying Library
#include <SPI.h> // Include dependant SPI Library
// custom lib
#include <myLowPower.h>
#include <myConfig.h>
#include "myRF_lib.h"
//
// Create Amplitude Shift Keying Object
#define transmitter_pin radio_trans_pin // connected to 315Mhz transmitter data line
#define transmission_rate 2000 // bits per second
RH_ASK driver(transmission_rate, 0, transmitter_pin, 0); // (bits/sec, rxPin, txPin(D3), pttPin)

/*
NOTE: if reducing mcu clock speed, transmission rate needs to be inversely proportional
      for example, if reducing clock from 8 to 4 Mhz, transmission speed needs to double
*/

//
void myRF_lib_c::init(){
    driver.init(); // rf driver
}
// send RF message
void myRF_lib_c::send_message(){

    for (uint8_t i = 0; i < 2; i++) { // sends message twice, I found that the first message doesnt always make it so a second one helps with redundancy
        String message = String(i); // sends 0 then 1, set to what ever you want
        const char* msg = message.c_str(); // convert string to char array
        driver.send((uint8_t*)msg, strlen(msg)); // send message
        driver.waitPacketSent(); // wait until message is sent
#ifdef debug
        Serial.print(F("sent: "));
        Serial.println(message);
        Serial.flush();
#endif
        // debounce sleep
        myLowPower.sleep_500MS();
        //LowPower.idle(SLEEP_500MS, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
    }
}

// ----------------
myRF_lib_c myRF_lib;
