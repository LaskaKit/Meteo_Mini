#include "Arduino.h"
#include <ESP32AnalogRead.h>    // local changes needed, we will try to change ESP32AnalogRead.h on GitHub
ESP32AnalogRead adc;
#define deviderRatio 1.7692 // 100 + 130kOhm
void setup()
{
	adc.attach(0);
	Serial.begin(115200);
}

void loop()
{
	delay(2000);                                                  // Example  1         2 
	Serial.println("Voltage adc= "+String(adc.readVoltage()));                //1.86    2.24
  Serial.println("Voltage bat = "+String(adc.readVoltage()*deviderRatio));  //3.33    4.02
  Serial.println("Raw = "+String(adc.readRaw()));                           //3.500   3088
}
