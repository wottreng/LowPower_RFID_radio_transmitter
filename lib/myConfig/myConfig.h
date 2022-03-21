#pragma once

#include <Arduino.h>
#include <string.h>

//#define debug true // uncomment to turn on serial output

// low power interrupt pin ---------
#define switch_pin 2
// rfid reader config --------------
#define rst_pin 8
#define ss_pin 10
#define reader_on_time 6000 // 6 seconds
// 315mHz radio config -------------
#define radio_trans_pin 3  // data pin
