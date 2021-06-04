/*
  Ballvalve.cpp - Control Library for the AIR/WATER/GAS Ball Valves 
  This one designed around the U.S.SOLID 5 Wire 
  USS-MSV00015 5 Wire Model with Full OPEN/CLOSED Status 
  Functionality requires the addition of a standard DPDT Relay module
  and 24VDC power supply
  https://www.youtube.com/c/jordanrubin6502
  Project Video:  https://www.youtube.com/watch?v=yC6QS6Ac-z0
  2020 Jordan Rubin.
*/

#include "Arduino.h" // Required for Platform.io
#include "Ballvalve.h"

int maxTraveltime;
unsigned long opentime,closetime;
bool usePowerRelay = false;
int defaultMaxtravelTime = 8;
int openStatus,closeStatus,valveRelay,powerRelay;
unsigned long currentMillis;

//CONSTRUCTOR -----------------------------------------------------------
//FIVEWIREVALVE (RelayGPIOpin, openStatusGPIOpin, closeStatusGPIOpin, useInternalPullups, powerRelayGPIOpin)
FIVEWIREVALVE::FIVEWIREVALVE(int RelayGPIOpin, int openStatusGPIOpin, int closeStatusGPIOpin, bool useInternalPullups, int powerRelayGPIOpin)
{
  //----------------- initialize initial parameters  
    maxTraveltime = defaultMaxtravelTime;
    usePowerRelay = true;
    if (useInternalPullups){
      pinMode(openStatusGPIOpin, INPUT_PULLUP);
      pinMode(closeStatusGPIOpin, INPUT_PULLUP);
    }
    else {
      pinMode(openStatusGPIOpin, INPUT);
      pinMode(closeStatusGPIOpin, INPUT);
    }
  pinMode(RelayGPIOpin, OUTPUT);
  pinMode(powerRelayGPIOpin, OUTPUT);
  openStatus = openStatusGPIOpin;
  closeStatus = closeStatusGPIOpin;
  valveRelay = RelayGPIOpin;
  powerRelay = powerRelayGPIOpin;
}
// ----------------------------------------------------------------------------]

//CONSTRUCTOR -----------------------------------------------------------
//FIVEWIREVALVE (RelayGPIOpin, StartStatusGPIOpin, StopStatusGPIOpin, useInternalPullups)
FIVEWIREVALVE::FIVEWIREVALVE(int RelayGPIOpin, int openStatusGPIOpin, int closeStatusGPIOpin, bool useInternalPullups)
{
  //----------------- initialize initial parameters
	maxTraveltime = defaultMaxtravelTime;
  if (useInternalPullups){
    pinMode(openStatusGPIOpin, INPUT_PULLUP);
    pinMode(closeStatusGPIOpin, INPUT_PULLUP);
  }
  else {
    pinMode(openStatusGPIOpin, INPUT);
    pinMode(closeStatusGPIOpin, INPUT);
  }
  pinMode(RelayGPIOpin, OUTPUT);
  openStatus = openStatusGPIOpin;
  closeStatus = closeStatusGPIOpin;
  valveRelay = RelayGPIOpin;
}
// ----------------------------------------------------------------------------]

// FUNCTION - [getValvePosition] - Returns [OPEN/CLOSED/MIDWAY/ERROR]----------]
const char* FIVEWIREVALVE::getValvePosition(void){
  int open_state = digitalRead(openStatus);
  int close_state = digitalRead(closeStatus);
  if (open_state == LOW ){return "OPEN";}
  if (close_state == LOW){return "CLOSED";}
  if ((open_state == HIGH)&&(close_state == HIGH)){return "MIDWAY";}
	return "ERROR";
}
// ----------------------------------------------------------------------------]

// FUNCTION - [getLastDuration] - [OPEN/CLOSE] Returns OPEN/CLOSE time---------]
int FIVEWIREVALVE::getLastDuration(const char* position){
  if (strcmp(position,"OPEN")==0){return opentime;}
    else if (strcmp(position,"CLOSED")==0){return closetime;}
    else {return 0;}
}
// ----------------------------------------------------------------------------]

// FUNCTION - [getMaxTravelTime] - Returns MaxTravelTime-----------------------]
int FIVEWIREVALVE::getMaxTravelTime(void){
	return maxTraveltime;
}
// ----------------------------------------------------------------------------]

// FUNCTION - [setMaxTravelTime] - Sets Max Travel Time--[int SEC]-------------]
void FIVEWIREVALVE::setMaxTraveltime(int time){
  maxTraveltime = time;
}
// ----------------------------------------------------------------------------]

// FUNCTION - [setValvePosition] -[OPEN/CLOSE]---------------------------------]
const char* FIVEWIREVALVE::setValvePosition(const char *position){	
  int count = 0;
  unsigned long starttime;
  unsigned long endtime;
  starttime = millis();
  bool hiLow = 1;
  if (strcmp(position,"CLOSED")==0){hiLow=0;}
  if (strcmp(getValvePosition(),position)==0){return "Already there";}
  if (usePowerRelay == true){digitalWrite(powerRelay,HIGH);delay(100);}
  digitalWrite(valveRelay,hiLow);
  while (strcmp(getValvePosition(),position)!=0){
    delay(1000);
    if (count > maxTraveltime){
      if (usePowerRelay == true){digitalWrite(powerRelay,LOW);} 
           return "Error";
      }    
      count++;
  }  
  if (usePowerRelay == true){digitalWrite(powerRelay,LOW);} 
  endtime = millis(); 
  if (strcmp(position,"OPEN")==0){opentime = (endtime - starttime) /1000;}
  else {closetime = (endtime - starttime) /1000;}    
  return position;
}
// ----------------------------------------------------------------------------]