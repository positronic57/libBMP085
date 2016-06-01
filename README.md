LibBMP085
===========
LibBMP085 is a simple, easy to use C library for communication with Bosh BMP085/BMP180 barometric pressure and temperature sensor
on Linux. It provides access to the BMP085/BMP180 sensor from the user space through the /dev interface. 
Module i2c-dev must be loaded before library use.

Supported sensors
--------------------
- Bosh BMP085;
- Bosh BMP180 (replacement for BMP085).

Implemented senor features
-----------------------

The library implements functions for: 
- connecting to BMP085/BMP180 sensor over I2C bus; 
- reading the sensor calibration table; 
- reads measured values from the sensor;
- calculating relative altitude change.
It supports all BMP085/BMP180 modes of operation.

Installation
---------------
Installation instruction can be found in the INSTALL file.

Test Hardware
---------------
Tested on Raspberry Pi model B Revision 1 board with:
- Adafruit BMP085 module (Adafruit product ID 391);
- Adafruit BMP180 module (Adafruit product ID 1603).
The library is distributed with an example program that demonstrates the library use for temperature and barometric pressure measurement. 

**WARNING:** 
The source is provided as it is without any warranty. Use it on your own risk!
The author does not take any responsibility for the damage caused while using this software.
