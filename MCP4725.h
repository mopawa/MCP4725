/**************************************************************************/
/*! 
    @file     MCP4725.cpp
    @author   Benoit Loyez
	@license  BSD (see license.txt)
	
	Arduino ESP-01 I2C Driver for Microchip's MCP4725 I2C DAC

	This is a library for the SparkFun MCP4725 breakout and similar hooked to an ESP-01 Arduino
	----> https://www.sparkfun.com/products/12918
		
	Derived from Adafruit_MCP4725 library

	@section  HISTORY

    v1.0 - First release
*/
/**************************************************************************/

#ifndef MCP4725_h
#define MCP4725_h

#include "Arduino.h"

#include <Wire.h>

#define MCP4725_ADR      (0x60)  // MCP4725 address | A0 connected to GND = 0x60, A0 connected to VCC = 0x61 | refer to https://learn.sparkfun.com/tutorials/mcp4725-digital-to-analog-converter-hookup-guide

class MCP4725
{
  public:
    MCP4725();
	void begin(); 
    void read(bool &err_r, uint16_t &dac_memory);
	void write(bool &err_w, uint16_t dac_value);
};

#endif