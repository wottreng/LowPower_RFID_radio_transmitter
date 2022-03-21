# LowPower_RFID_radio_transmitter
Arduino pro mini RFID reader with 315Mhz signal transmitter and Low Power consumption

Purpose: send radio signal when rfid is authorized. \
Written by: Mark Wottreng

## Project hardware
* arduino pro mini 8Mhz 3.3V: https://amzn.to/3IDkcBo
* arduion uno:
* usb to uart module: https://amzn.to/3G2czTF
* 315Mhz transmitter: https://amzn.to/3KJkp7X
    * antenna length: 22.6cm or 8.9in
* light switch: https://amzn.to/3H5FVlo
* housing: https://amzn.to/3FVdwgt
* rfid reader MFRC522 module:
* battery: AA duracell battery, nominal voltage = 1.65v
-----------
## software
compiled with PlatformIO

-----------------
lib dependandencies:
* LowPower_LowPowerLab : https://github.com/LowPowerLab/LowPower
* RadioHead : https://www.airspayce.com/mikem/arduino/RadioHead/
* MFRC522 : https://github.com/miguelbalboa/rfid
--------------------
## Power Usage (measured with multimeter)
- arduino pro mini: 4.5 ma
- arduino pro mini with low power enabled and power led: 2 ma
- pro mini with low power sleep forever and power led removed: 0.08 ma
- rc522 out of box:  29 mA
- rc522 with power led and R2 removed, power on, 6 ma
- rc522 with power led and R2 removed, in hard sleep (rst to grnd): 0.01 ma


<p>
with 2 AA duracell batterys in series for power: ~3.3v.
assuming 1 amp-hour available from battery pack:
1000mA/0.08 = 12500 hours or 520 days.
With each use this will drop.
</p>

## Wire it up -----
<b> ** arduino pro mini ** </b>

hardware ref: https://www.arduino.cc/en/pmwiki.php?n=Main/ArduinoBoardProMini \
note: interrupt pins: 2 or 3

** Connections during flash for arduino pro mini **
- FT323 to arduino pro mini
- CTS -> GND
- RTS -> DTR
- RX -> TX
- TX -> RX
- GND -> GND
- VCC -> VCC \
=============== \
<b> ** arduino pro mini connections: **</b>
    note: onboard LED = pin 9
- RFID-RC522 RST  -> 8
- RFID-RC522 SS/SDA   -> 10
- RFID-RC522 MOSI -> 11
- RFID-RC522 MISO -> 12
- RFID-RC522 SCK  -> 13
- switch          -> 2
- 315Mhz trans    -> 3
----------
<b> ** arduino uno ** </b>

arduino uno connections:
- RFID-RC522 RST  -> 9
- RFID-RC522 SS/SDA   -> 10
- RFID-RC522 MOSI -> 11
- RFID-RC522 MISO -> 12
- RFID-RC522 SCK  -> 13
- switch          -> 2
- 315Mhz trans    -> 3

## Documentation
rfid RC522:
- https://lastminuteengineers.com/how-rfid-works-rc522-arduino-tutorial/
- https://components101.com/microcontrollers/arduino-pro-mini
- low power mode: https://github.com/miguelbalboa/rfid/issues/269

Cheers,
Mark
