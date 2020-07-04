# ballvalve
5 wire ball valve control library for Arduino/ Esp32 

I had written this library in support of a lrger irrigation project for the ESP32 though this is an entirely independent library that support a 5 wire ball valve.
I will post a link to the video here as soon as its published.

5 wire means:

    2 wires in support of the DC that actuates the more for open and closing of the valve
    3 wires in support of the reading of the valve position.


The particular motor being used for this project is the US SOLID USSMSV00015 This motor works with 9-24VDC though one should consider a power supply closer to 24V for better operation and longer life.  also Consider that the 2 wires for open closed operate as a flipflop. So a DPDT relay will also be required for this application.  This particular model, has automatic power off at both extremes of motion so a power relay is not required though may be desired to shut off the 24 power supply when not in use. Should you choose to employ a power relay as well, a parameter on creation of the instance of the object can configure that.    

The remaining three wires , common open and closed support the position of the valve, OPEN/CLOSED or MIDWAY.  Which can be quireied through the library and are also used by other functions of the library for operation.

