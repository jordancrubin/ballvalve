/*
  BALLVALVE.h - Control Library for the AIR/WATER/GAS Ball Valves 
  This one designed around the U.S.SOLID 5 Wire 
  USS-MSV00015 5 Wire Model with Full OPEN/CLOSED Status 
  Functionality requires the addition of a standard Relay module
  Copyright (c) 2020 Jordan Rubin.  All rights reserved.
  Functionality requires the addition of a standard Relay module*/

#include "Arduino.h"
#include "BALLVALVE.h"

int maxTraveltime;
char version[6] = "1.0.0";
int defaultMaxtravelTime = 8;
int openStatus,closeStatus,valveRelay;
unsigned long currentMillis;

//CONSTRUCTOR -----------------------------------------------------------
//FIVEWIREVALVE (RelayGPIOpin, openStatusGPIOpin, closeStatusGPIOpin, useInternalPullups, maxTravelTime)
FIVEWIREVALVE::FIVEWIREVALVE(int RelayGPIOpin, int openStatusGPIOpin, int closeStatusGPIOpin, bool useInternalPullups, int maxTime)
{
  //----------------- initialize initial parameters
  maxTraveltime = maxTime;
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
//CONSTRUCTOR -----------------------------------------------------------
//FIVEWIREVALVE (RelayGPIOpin, StartStatusGPIOpin, StopStatusGPIOpin, useInternalPullups)
FIVEWIREVALVE::FIVEWIREVALVE(int RelayGPIOpin, int openStatusGPIOpin, int closeStatusGPIOpin, bool useInternalPullups)
{
  //----------------- initialize initial parameters
	maxTraveltime = defaultMaxtravelTime;
  if (useInternalPullups){
    pinMode(openStatusGPIOpin, INPUT_PULLDOWN);
    pinMode(closeStatusGPIOpin, INPUT_PULLDOWN);
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

// FUNCTION - [getValvePosition] - Returns [OPEN/CLOSED/MIDWAY/ERROR]----------]
char* FIVEWIREVALVE::getValvePosition(void){
  int open_state = digitalRead(openStatus);
  int close_state = digitalRead(closeStatus);
  if (open_state == HIGH ){return "OPEN";}
  if (close_state == HIGH){return "CLOSED";}
  if ((open_state == LOW)&&(close_state == LOW)){return "MIDWAY";}
	return "ERROR";
}
// ----------------------------------------------------------------------------]

// FUNCTION - [getVersion] - Returns current Library revision------------------]
char* FIVEWIREVALVE::getVersion(void){
	return version;
}
// ----------------------------------------------------------------------------]

// FUNCTION - [getVersion] - Returns current Library revision------------------]
int FIVEWIREVALVE::getMaxTravelTime(void){
	return maxTraveltime;
}
// ----------------------------------------------------------------------------]

// FUNCTION - [getVersion] - Returns current Library revision------------------]
void FIVEWIREVALVE::setMaxTraveltime(int time){

  maxTraveltime = time;
}
// ----------------------------------------------------------------------------]

// FUNCTION - [setValvePosition] -[OPEN/CLOSE]---------------------------------]
char* FIVEWIREVALVE::setValvePosition(char* position){	
  int count =0;
  if (position == "OPEN"){
    if (strcmp(getValvePosition(),"OPEN")==0){return "Already Open";}
     digitalWrite(valveRelay,HIGH);
     while (strcmp(getValvePosition(),"OPEN")!=0){
      delay(1000);
      if (count > maxTraveltime){return "Error";}
      count++;
     }
  return "OPENED";
  }
  if (position == "CLOSED"){
    if (strcmp(getValvePosition(),"CLOSED")==0){return "Already Closed";}
     digitalWrite(valveRelay,LOW); 
    while (strcmp(getValvePosition(),"CLOSED")!=0){
      delay(1000);
      if (count > maxTraveltime){return "Error";}
      count++;
     }   
  return "CLOSED";   
  }
  return "ERR";
}
// ----------------------------------------------------------------------------]