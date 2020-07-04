# ballvalve
5 wire ball valve control library for Arduino/ Esp32 

I had written this library in support of a lrger irrigation project for the ESP32 though this is an entirely independent library that support a 5 wire ball valve.
I will post a link to the video here as soon as its published.

5 wire means:

    2 wires in support of the DC that actuates the motor for open and closing of the valve
    3 wires in support of the reading of the valve position.


The particular motor being used for this project is the US SOLID USSMSV00015 This motor works with 9-24VDC though one should consider a power supply closer to 24V for better operation and longer life.  Also, Consider that the 2 wires for open closed operate as a flipflop. So a DPDT relay module will also be required for this application.  This particular model has automatic power off at both extremes of motion so a power relay is not required, though may be desired to shut off the 24 power supply when not in use. Should you choose to employ or require a power relay, a parameter on creation of the instance of the object can configure that.    

The remaining three wires , common open and closed sense support the position of the valve, OPEN/CLOSED or MIDWAY.  Which can be queried through the library and are also used by other functions of the library for operation.


    CONSTRUCTOR: [with power relay]
FIVEWIREVALVE(RelayGPIOpin,StartStatusGPIOpin,StopStatusGPIOpin,useInternalPullups,powerGPIOpin)

FIVEWIREVALVE(int,int,int,bool,int);

'Ballvalve only contains one flavour of constructor, FIVEWIREVALVE, bacuase i dont collect these things, as I come across another one, ill add it.'

  RelayGPIOpin       -  This is the GPIO for the DPDT relay [which needs to be wired as a flipflip, see video]
  StartStatusGPIOpin -  This is the GPIO for the Closed position sense line
  StopStatusGPIOpin  -  This is the GPIO for the Opened position sense line
  useInternalPullups -  If you have an ESP32 and want to use internal pullup resistors instead of your own, set to true
  powerGPIOpin       -  This is the GPIO for the optional power relay, only supply this if using a power relay
  
    CONSTRUCTOR: [without power relay]
FIVEWIREVALVE(RelayGPIOpin,StartStatusGPIOpin,StopStatusGPIOpin,useInternalPullups)

FIVEWIREVALVE(int,int,int,bool);

  
  
  setMaxTraveltime(int)  - This should be set in setup, default value is 8 seconds.  This is the amount of time of an OPEN/CLOSE operation request runs before an error is returned.  You can have a program figure this normal value out from the getLastDuration() function.
  
  getLastDuration(OPEN|CLOSED) - Returs the number of seconds of the last sucessful execution of this action. This can be used to refactor into setMaxTraveltime plus the addition of a buffer of 1 or more seconds.


  

    char* getValvePosition(void); 
    void setMaxTraveltime(int);
    char* setValvePosition(char*);

