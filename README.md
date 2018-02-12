# MCP4725


Arduino ESP-01 I2C Driver for Microchip's MCP4725 I2C DAC

This is a library for the SparkFun MCP4725 breakout and similar, hooked to an ESP-01 Arduino

<https://www.sparkfun.com/products/12918>
		
Derived from the Adafruit_MCP4725 library

<https://github.com/adafruit/Adafruit_MCP4725>

This chip uses I2C to communicate, 2 pins are required to 
interface.

## Connect ESP-01 and MCP4725

Connect ESP01 GPIO0 to MCP4725 SDA and GPIO2 to SCL


## Download and install

To download, click the DOWNLOADS button in the top right corner, rename the uncompressed folder MCP4725. Check that the MCP4725 folder contains MCP4725.cpp and MCP4725.h

Place the MCP4725 library folder in your arduinosketchfolder/libraries/ folder. You may need to create the libraries subfolder if its your first library. Restart the IDE.

## License

BSD license, check LICENSE file for more information.
All text above must be included in any redistribution