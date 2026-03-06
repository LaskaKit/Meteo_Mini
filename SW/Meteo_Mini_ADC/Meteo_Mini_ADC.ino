/*
* LaskaKit Meteo Mini board reads voltage on Battery
* and sends every 2 seconds through UART
* 
* Board:   LaskaKit Meteo Mini C3      https://www.laskakit.cz/laskakit-meteo-mini/
*          LaskaKit Meteo Mini C6      
* 
* 
* Made by laskakit.cz (c) 2026
*/

#include <SPI.h>
#include <Wire.h>

#define Meteo_Mini_C3
//#define Meteo_Mini_C6

#if defined(Meteo_Mini_C3)

  #define ADCpin  0

#elif defined(Meteo_Mini_C6)

  #define ADCpin  3

#endif


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
