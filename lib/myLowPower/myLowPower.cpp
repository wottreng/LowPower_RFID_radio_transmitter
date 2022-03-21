#include <Arduino.h>
#include <LowPower.h>
//
#include <myConfig.h>
#include "myLowPower.h"
//
#define switchPin switch_pin // rocker switch input pin
//
void myLowPower_c::init(){
    pinMode(switchPin, INPUT_PULLUP); // pulled high by internal resistor
}
//
void wakeUp()
{
    // Just a handler for the pin interrupt.
}
// attach interrupt and go to sleep until woke up by switch pin
void myLowPower_c::loop(){
    attachInterrupt(digitalPinToInterrupt(switchPin), wakeUp, CHANGE);
    LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);
    detachInterrupt(switchPin);
}

void myLowPower_c::sleep_500MS(){
    LowPower.idle(SLEEP_500MS, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF); 
}
void myLowPower_c::sleep_120MS(){
    LowPower.idle(SLEEP_120MS, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF); 
}

//
myLowPower_c myLowPower;