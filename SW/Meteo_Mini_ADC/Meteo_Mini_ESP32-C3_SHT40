/*
* Vzorovy kod od laskarduino.cz pro SHT40 s vyvojovym kitem Meteo Mini s ESP32-C3
* Kod posle pres seriovy port (UART)
* hodnoty teploty a vlhkosti z SHT40
* kazdou sekundu
*
* SDA - GPIO19
* SCL - GPIO18
*
* Vytvoreno (c) laskarduino.cz 2023
*
* Potrebne knihovny:
* https://github.com/adafruit/Adafruit_SHT4X
*/
 
#include <Wire.h>
#include "Adafruit_SHT4x.h"
 
Adafruit_SHT4x sht4 = Adafruit_SHT4x();
 
void setup() {
  Serial.begin(115200);
  while (!Serial) 
  {
    ; // cekani na Serial port
  }

  Wire.begin(19, 18); // SDA, SCL
 
  if (! sht4.begin()) 
  {
    Serial.println("SHT4x nenalezen");
    Serial.println("Zkontrolujte propojeni");
    while (1) delay(1);
  }
 
  sht4.setPrecision(SHT4X_HIGH_PRECISION); // nejvyssi rozliseni
  sht4.setHeater(SHT4X_NO_HEATER); // bez vnitrniho ohrevu
 
}
 
void loop() {
  sensors_event_t humidity, temp; // promenne vlhkost a teplota
 
  sht4.getEvent(&humidity, &temp);
  Serial.print("Teplota: "); Serial.print(temp.temperature); Serial.println(" degC");
  Serial.print("Vlhkost: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");
 
  delay(1000);
}
