/*
  BALLVALVE.h - Control Library for the AIR/WATER/GAS Ball Valves 
  This one designed around the U.S.SOLID 5 Wire 
  USS-MSV00015 5 Wire Model with Full OPEN/CLOSED Status 
  Functionality requires the addition of a standard Relay module
  Copyright (c) 2020 Jordan Rubin.  All rights reserved.
  Functionality requires the addition of a standard Relay module*/

// ensure this library description is only included once
#ifndef BALLVALVE_h
#define BALLVALVE_h

// include types & constants of Wiring core API

// library interface description
class FIVEWIREVALVE
{
  ////////////// user-accessible "public" interface
  //FIVEWIREVALVE(RelayGPIOpin,StartStatusGPIOpin,StopStatusGPIOpin,maxTravelTime)
  public:
    FIVEWIREVALVE(int,int,int,bool,int);
    FIVEWIREVALVE(int,int,int,bool);
    int catClarifier(char*);
    int catClarifierfreq(char*,char*);
    int catCtcssdcs(char*);
    int getMaxTravelTime(void);
    char* getValvePosition(void); 
    char* getVersion(void);
    void setMaxTraveltime(int);
    char* setValvePosition(char*);

  ////////////// library-accessible "private" interface
  private:
    int value;
//    void loadConstants(void);
//    Print* printer;
    
};

#endif
