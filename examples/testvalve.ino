/*
  testvalve.ino/cpp - Test programme for the AIR/WATER/GAS Ball Valves 
  This one designed around the U.S.SOLID 5 Wire 
  USS-MSV00015 5 Wire Model with Full OPEN/CLOSED Status 
  Functionality requires the addition of a standard DPDT Relay module
  and 24VDC power supply
  https://www.youtube.com/c/jordanrubin6502
  2020 Jordan Rubin.
  */

#include <Arduino.h> // Enable for Platform.io
#include <Ballvalve.h>

// New Instance (RelayGPIOpin, openStatusGPIOpin, closeStatusGPIOpin, useInternalPullups,PowerRelayGPIOpin)
// Following the Youtube video above as part of this project The GPIO Pins would be 16,17, and 18.  The ESP32 has
// Internal pull-up resistors so the next option is set to true, if you device does not, you can set to false and 
// Use pull up resistors for the connections on 17 and 18.  If you are using internal pullups, set the next value 
// to true, if you are supplying your own pull up resistors for the last 2 values, cloose false. Finally, If you 
// wish to have the power supply [24vdc] that you must supply, controlled by the esp32, to be energized only during
// open and close operations, you must supply a SPST relay and that relay's GPIO pin here.  If no value the program 
// will assume no Power relay.

// MOTOR RELAY ON 16
// OPEN/CLOSE SENSE on 17&18
// USE INTERNAL PULLUPS [ESP32]
// NO POWER SUPPLY RELAY
FIVEWIREVALVE thisValve(16,17,18,true);

void setup() {
 Serial.begin(38400);
 thisValve.setMaxTraveltime(9);  // If you do not set a travel time, the default is 8 seconds.
}

void loop() {
    delay(10000);
    Serial.println("START CYCLE\n\n");
    Serial.print("Max Travel Time set to: "); Serial.println(thisValve.getMaxTravelTime());
    Serial.print("Valve position currently: "); Serial.println(thisValve.getValvePosition());
    delay(1000);
    Serial.println("OPENING REQUEST->\n\n");
    Serial.println(thisValve.setValvePosition("OPEN"));
    delay(10000);
    Serial.println("CLOSING REQUEST->\n\n");
    Serial.println(thisValve.setValvePosition("CLOSED"));
}