/*
* This example code is used for LaskaKit Meteo Mini board 
*
* Meteo Mini ESP board reads voltage on Battery and Solar panel 
* and sends every 2 seconds through UART
* 
*
* Made by (c) laskakit.cz 2022
* 
*/

#include <SPI.h>
#include <Wire.h>

#define ADCpin 0
#define DeviderRatio 1.7693877551  // Voltage devider ratio on ADC pin 1MOhm + 1.3MOhm

void setup() {
    
  Serial.begin(115200);
  delay(100); // let serial console settle
}

void loop() {

  float bat_voltage = analogReadMilliVolts(ADCpin) * DeviderRatio / 1000;
  Serial.print("Battery Voltage = " );
  Serial.print(bat_voltage);
  Serial.println("V");

  delay(2000);
}
