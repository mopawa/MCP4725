/**************************************************************************/
/*! 
    @file     MCP4725.cpp
    @author   Benoit Loyez
	@license  BSD (see license.txt)
	
	Arduino ESP-01 I2C Driver for Microchip's MCP4725 I2C DAC

	This is a library for the SparkFun MCP4725 breakout and similar
	----> https://www.sparkfun.com/products/12918
		
	Derived from Adafruit_MCP4725 library

	@section  HISTORY

    v1.0 - First release
*/
/**************************************************************************/

#include "Arduino.h"
#include <Wire.h>
#include "MCP4725.h"

/**************************************************************************/
/*! 
    @brief  Instantiates a new MCP4725 class
*/
/**************************************************************************/
MCP4725::MCP4725() {
}

/**************************************************************************/
/*! 
    @brief  Setups the HW
*/
/**************************************************************************/
void MCP4725::begin() {
  Wire.begin(0, 2); // For ESP-01, set SDA: GPIO0, SCL: GPIO2
}

void MCP4725::read(bool &err_r, uint16_t &dac_memory)
{
  uint8_t err = Wire.requestFrom(MCP4725_ADR, 5);    // We want to read 5 bytes from the MCP4725 (refer to MCP4725 datasheet)

  if (err == 5) // Test if 5 bytes were received
  {
    uint8_t count = 0;
    uint16_t dac_r;
    uint16_t eeprom_r;
    while(Wire.available()) // Cycle through received bytes
      { 
        uint8_t c = Wire.read();    // Store byte
     
        switch (count) // 1st byte does not contain data, we need to process the 4 other bytes
          {
            case 1: // 2nd byte = DAC D11 to D4
              dac_r = c << 4; // 8 bits to 12 bits conversion 
            break;
            case 2: // 3rd byte = DAC D3 to D0
              dac_r = dac_r | (c >> 4); // 4 bits to 12 bits conversion + added to previous value
            break;
            case 3: // 4th byte = EEPROM D11 to D8
              eeprom_r = (c << 8); // 4 bits to 12 bits conversion
            break;
            case 4: // 5th byte = EEPROM D7 to D0
              eeprom_r = eeprom_r | c; // added to previous value
            break;
		   }
      count++;
      }
    if (dac_r == eeprom_r) // Verify if values are consistent between MCP4725 DAC register and its EEPROM
    {
      dac_memory = eeprom_r; // Returns DAC value
	  err_r = false; // Returns no read error
    }
    else
    {
      dac_memory = 0;
	  err_r = true; // Returns read error
    }
  }
  else
  {
     dac_memory = 0;
	 err_r = true; // Returns read error
  }
}

void MCP4725::write(bool &err_w, uint16_t dac_value)
{
  
  if (dac_value > 4095)
   {
     dac_value = 4095; // To avoid writing a value bigger than 12 bits
   }
  Wire.beginTransmission(MCP4725_ADR);
  Wire.write(96); // The first byte transmitted defines the write mode (96 = writes to DAC register and EEPROM) | Refer to MCP4725 datasheet
  Wire.write(dac_value >> 4);                   // Upper data bits          (D11.D10.D9.D8.D7.D6.D5.D4)
  Wire.write((dac_value & 15) << 4);            // Lower data bits          (D3.D2.D1.D0.x.x.x.x)
  uint8_t err = Wire.endTransmission(); // Stores error value, should be 0 if no error
  delay(50); // Without this delay, a subsequent read would fail - not sure why?
  if (err != 0)
  {
    err_w = true; // Returns write error
  }
  else
  {
    err_w = false; // Returns no write error
  }
}