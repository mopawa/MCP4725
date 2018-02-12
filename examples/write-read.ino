#include <Wire.h>
#include <MCP4725.h>

MCP4725 dac;

void setup()
{
  Serial.begin(115200); // We open serial connection to console
  Serial.println("Hello!");
  dac.begin(); // Sets ESP-01 pins
}

// 
void loop()
{
  // We will write a value to the DAC register and EEPROM of the MCP4725.
  // Value must be between 0 and 4095 (12 bits) and stored in dac_value
  // After power off, the value will be automatically restored by the MCP4725 to its DAC register from its EEPROM
  
  Serial.println("Write BEGIN");
  bool err_w; // false = no write error / true = write error
  uint16_t dac_value = 2096; // the value we want to transfer
  dac.write(err_w, dac_value); // Value transfer to MCP4725
  Serial.println(err_w);
  Serial.println("Write END\n");

  // The good thing with MCP4725 is that we can read the EEPROM stored value even after a reset/power off  
  Serial.println("Read BEGIN");
  bool err_r; // false = no read error / true = read error
  uint16_t dac_memory; // the value stored in MCP4725 EEPROM
  dac.read(err_r, dac_memory); // Read value from MCP4725
  Serial.println(err_r);
  Serial.println(dac_memory);
  Serial.println("Read END");
  delay(5000); // Let's sleep a little!
}  
