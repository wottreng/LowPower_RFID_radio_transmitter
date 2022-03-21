#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>
#include <string.h>
//
#include "myNFC.h"
#include <myConfig.h>
#include <myLowPower.h>

// extern const bool debug;
//
#define RST_PIN rst_pin
#define SS_PIN ss_pin

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance

MFRC522::MIFARE_Key nfc_key;

// power on/off rfid reader
void myNFC_c::power_off_reader()
{
    digitalWrite(RST_PIN, 0);
}
//
void myNFC_c::start_rfid_reader()
{
  //digitalWrite(RST_PIN, 1);
  mfrc522.PCD_Init();
}
// -----
void myNFC_c::init()
{
#ifndef SPI
    SPI.begin(); // Init SPI bus
#endif
    //mfrc522.PCD_Init();
    //
    //  Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
    for (uint8_t i = 0; i < 6; i++)
        nfc_key.keyByte[i] = 0xFF;
    //
    // mfrc522.PCD_SoftPowerDown();
    myNFC.power_off_reader();
}
//
bool check_passwd(uint8_t buffer[])
{
    uint8_t passwd[] = { 0x67, 0x63, 0x43, 0x61, 0x65, 0x65, 0x42 };
#ifdef debug
    Serial.println(F("check passwd"));
    Serial.flush();
#endif
    // Serial.println(buffer[0], HEX);
    uint8_t match = 0;
    for (byte i = 0; i < 7; i++) {
        if (buffer[i] == passwd[i]) {
            match++;
        }
    }
#ifdef debug
    Serial.print(F("match: "));
    Serial.println(match);
    Serial.flush();
#endif
    if (match == 7) {
        return true;
    } else
        return false;
}
// ---------
bool myNFC_c::loop()
{

    // some variables we need
    uint8_t block = 4;
    uint8_t len = 18;
    MFRC522::StatusCode status;

    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if (!mfrc522.PICC_IsNewCardPresent()) {
        return false;
    }

    // Select one of the cards
    if (!mfrc522.PICC_ReadCardSerial()) {
        return false;
    }

#ifdef debug
    Serial.println(F("**Card Detected:**"));
    Serial.flush();
#endif
    //--------------
    // mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card
    // mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

    //-------------------------------------------
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &nfc_key, &(mfrc522.uid)); // line 834 of MFRC522.cpp file
    if (status != MFRC522::STATUS_OK) {
#ifdef debug
        Serial.print(F("Authentication failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        Serial.println(F("tip: Check your card auth keys"));
        Serial.flush();
#endif
        // delay(1000);
        myLowPower.sleep_500MS(); // power optimization
        return false;
    }
    uint8_t buffer1[18];
    status = mfrc522.MIFARE_Read(block, buffer1, &len);
    if (status != MFRC522::STATUS_OK) {
#ifdef debug
        Serial.print(F("Reading failed: "));
        Serial.println(mfrc522.GetStatusCodeName(status));
        Serial.flush();
#endif
        // delay(100);
        myLowPower.sleep_120MS(); // power optimization
        return false;
    }
//
#ifdef debug
    for (uint8_t i = 0; i < 16; i++) {
        Serial.print(buffer1[i], HEX);
        Serial.print(" ");
    }
    Serial.println("!");
    Serial.flush();
#endif
    //
    bool passwd_id = check_passwd(buffer1);
#ifdef debug
    if (passwd_id == true) {
        Serial.println(F("passwd matches, open garage"));
        Serial.flush();
    }
    Serial.println(F("**End Reading**"));
    Serial.flush();
#endif
    // delay(500); // change value if you want to read cards faster
    myLowPower.sleep_500MS(); // power usage optimization

    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();
    //
    // mfrc522.PCD_SoftPowerDown();
    if (passwd_id == true) {
        return true;
    } else {
        return false;
    }
}

myNFC_c myNFC;

/*
VCC supplies power for the module. This can be anywhere from 2.5 to 3.3 volts. You can connect it to 3.3V output from your Arduino. Remember connecting it to 5V pin will likely destroy your module!

RST is an input for Reset and power-down. When this pin goes low, hard power-down is enabled. This turns off all internal current sinks including the oscillator and the input pins are disconnected from the outside world. On the rising edge, the module is reset.

GND is the Ground Pin and needs to be connected to GND pin on the Arduino.

IRQ is an interrupt pin that can alert the microcontroller when RFID tag comes into its vicinity.

MISO / SCL / Tx pin acts as Master-In-Slave-Out when SPI interface is enabled, acts as serial clock when I2C interface is enabled and acts as serial data output when UART interface is enabled.

MOSI (Master Out Slave In) is SPI input to the RC522 module.

SCK (Serial Clock) accepts clock pulses provided by the SPI bus Master i.e. Arduino.

SS / SDA / Rx pin acts as Signal input when SPI interface is enabled, acts as serial data when I2C interface is enabled and acts as serial data input when UART interface is enabled. This pin is usually marked by encasing the pin in a square so it can be used as a reference for identifying the other pins.
*/
