 /*
  testvalve example - for the AIR/WATER/GAS Ball Valves 
  This one designed around the U.S.SOLID 5 Wire 
  USS-MSV00015 5 Wire Model with Full OPEN/CLOSED Status 
  Functionality requires the addition of a standard DPDT Relay module
  https://www.youtube.com/c/jordanrubin6502
  2020 Jordan Rubin.
*/

// #include <Arduino.h> // Enable for Platform.io
#include <Ballvalve.h>

// New Instance (RelayGPIOpin, openStatusGPIOpin, closeStatusGPIOpin, useInternalPullups, maxTravelTime)
// Following the Youtube video above as part of this project The GPIO Pins would be 16,17, and 18.  The ESP32 has
// Internal pull-up resistors so the next option is set to true, if you device does not, you can set to false and 
// Use pull up resistors for the connections on 17 and 18.  If you Do not set maxTravelTime, it will defailt to 8 
// seconds.
FIVEWIREVALVE thisValve(16,17,18,true,8);

void setup() {
 Serial.begin(38400);
}

void loop() {
    delay(10000);
    Serial.println("START");
    Serial.println(thisValve.getVersion());
    Serial.println(thisValve.getValvePosition());
    delay(3000);
    Serial.println("OPENING");
    Serial.println(thisValve.setValvePosition("OPEN"));
    delay(10000);
    Serial.println("CLOSING");
    Serial.println(thisValve.setValvePosition("CLOSED"));
}
