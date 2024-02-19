/*
 * Example code for SCD41 (CO2 sensor) and MeteoMini board with ESP32-C3
 * Values are sent to Serial Monitor
 * 
 * Boards:
 * https://www.laskakit.cz/laskakit-meteo-mini/
 * https://www.laskakit.cz/laskakit-scd41-senzor-co2--teploty-a-vlhkosti-vzduchu/
 * 
 * 
 * Library:
 * https://github.com/sparkfun/SparkFun_SCD4x_Arduino_Library
 *
 * GPIO19 - SDA
 * GPIO18 - SCL
 * 
 * Made by laskakit.cz (c) 2023
  */
  
#include <Wire.h>
#include "SparkFun_SCD4x_Arduino_Library.h"
#define SDA 19
#define SCL 18
#define PIN_ON 3

SCD4x SCD41;

void setup() {
  Serial.begin(115200);
  // for version over 3.5 need to turn uSUP ON
  pinMode(PIN_ON, OUTPUT);      // Set EN pin for uSUP stabilisator as output
  digitalWrite(PIN_ON, HIGH);   // Turn on the uSUP power

  Wire.begin(SDA, SCL);

  Serial.println("SCD41 and MeteoMini example code");
  //             begin, autoCalibrate
  //               |      |
  if (SCD41.begin(false, true) == false)
  {
    Serial.println("SCD41 was not set correctly. Check the connection.");
    while (1)
      ;
  }

  if (SCD41.startLowPowerPeriodicMeasurement() == true)  {
    Serial.println("Low power mode enabled.");
  }
}

void loop() {
  if (SCD41.readMeasurement()) // wait for a new data (approx 30s)
  {
    Serial.println();

    Serial.print("CO2(ppm):");
    Serial.println(SCD41.getCO2());

    Serial.print("Temperature(C):");
    Serial.println(SCD41.getTemperature(), 1);

    Serial.print("Humidity(%RH):");
    Serial.println(SCD41.getHumidity(), 1);

    Serial.println();
  }

  delay(1000);
}
