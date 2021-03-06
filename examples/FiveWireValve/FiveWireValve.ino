/*
  Rename file to main.cpp to compile example in platform.io
  testvalve.ino/cpp - Test programme for the AIR/WATER/GAS Ball Valves 
  This one designed around the U.S.SOLID 5 Wire 
  USS-MSV00015 5 Wire Model with Full OPEN/CLOSED Status 
  Functionality requires the addition of a standard DPDT Relay module
  and 24VDC power supply
  https://www.youtube.com/c/jordanrubin6502
  Project Video:  https://www.youtube.com/watch?v=yC6QS6Ac-z0
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
// If you do not set a travel time, the default is 8 seconds.  This is the maximum amount of time it should take to
// get from open to closed or closed to open.  The function checks between both stops when setValvePosition executes.
// If the time taken should exceed this value, an ERROR will be returned as a statusn through the valve still might 
// have eventually reached the full position.  This can be seperately polled later to see if it is stuck with the
// getValvePosition function.  Your program should incorperate this polling or alarm on error. 
  thisValve.setMaxTraveltime(9);  
  Serial.println("\n\n***VALVE DEMO PROGRAMME***\n\n");
}

void loop() {   
    Serial.println("\nSTART CYCLE----------------------|");
    // Returns the MaxTravelTime value in seconds either the default or the one set by setMaxTraveltime.
    Serial.print("Max Travel Time set to: "); Serial.println(thisValve.getMaxTravelTime());
    //Returns the current position of the value.  OPEN / CLOSED / or MIDWAY
    Serial.print("Valve position currently: "); Serial.println(thisValve.getValvePosition());
    delay(1000);
    Serial.print("OPENING REQUEST-> ");
    // Orchestrates the opening of the valve, incorperates the OPEN/CLOSE sense and maxtime
    Serial.println(thisValve.setValvePosition("OPEN"));
    delay(20000);
    Serial.print("CLOSING REQUEST-> ");
    // Orchestrates the closing of the valve, incorperates the OPEN/CLOSE sense and maxtime
    Serial.println(thisValve.setValvePosition("CLOSED"));
    // Returns the duration of the LAST sucessful OPEN and CLOSE event in seconds, allowing a program to
    // Re-calibrate the MaxTravelTime if need be.
    Serial.print("Last OPEN  took: "); Serial.print(thisValve.getLastDuration("OPEN")); Serial.println(" seconds.");
    Serial.print("Last CLOSE took: "); Serial.print(thisValve.getLastDuration("CLOSED")); Serial.println(" seconds.");
    Serial.println("|------------------------END CYCLE\n");
    delay(20000);
}
