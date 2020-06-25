/*
  Ballvalve.h - Control Library for the AIR/WATER/GAS Ball Valves 
  This one designed around the U.S.SOLID 5 Wire 
  USS-MSV00015 5 Wire Model with Full OPEN/CLOSED Status 
  Functionality requires the addition of a standard DPDT Relay module
  and 24VDC power supply
  https://www.youtube.com/c/jordanrubin6502
  2020 Jordan Rubin.
  */

// ensure this library description is only included once
#ifndef Ballvalve_h
#define Ballvalve_h

// library interface description
class FIVEWIREVALVE
{
  ////////////// user-accessible "public" interface
  //FIVEWIREVALVE(RelayGPIOpin,StartStatusGPIOpin,StopStatusGPIOpin,useInternalPullups,powerGPIOpin)
  public:
    FIVEWIREVALVE(int,int,int,bool,int);
    FIVEWIREVALVE(int,int,int,bool);
    int getMaxTravelTime(void);
    char* getValvePosition(void); 
    void setMaxTraveltime(int);
    char* setValvePosition(char*);
  ////////////// library-accessible "private" interface
  private:
    int value;
};

#endif
