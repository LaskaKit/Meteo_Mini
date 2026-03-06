/*
* Vzorovy kod od laskakit.cz pro SHT40 s vyvojovym kitem Meteo Mini s ESP32-C3
* Kod posle pres seriovy port (UART)
* hodnoty teploty a vlhkosti z SHT40
* kazdou sekundu
* Boards:
* https://www.laskakit.cz/laskakit-meteo-mini/
* https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/
* SDA - GPIO19
* SCL - GPIO18
*
* Vytvoreno (c) laskakit.cz 2023
*
* Potrebne knihovny:
* https://github.com/adafruit/Adafruit_SHT4X
*/
 
#include <Wire.h>
#include "Adafruit_SHT4x.h"

//#define Meteo_Mini_C3
#define Meteo_Mini_C6

#if defined(Meteo_Mini_C3)

  #define Power   4
  #define SCL     18
  #define SDA     19 

#elif defined(Meteo_Mini_C6)

  #define Power   1
  #define SCL     5
  #define SDA     4 

#endif

Adafruit_SHT4x sht4 = Adafruit_SHT4x();
 
void setup() {
  Serial.begin(115200);
  while (!Serial) 
  {
    ; // cekani na Serial port
  }

  // for version over 3.5 need to turn uSUP ON
  pinMode(Power, OUTPUT);      // Set EN pin for uSUP stabilisator as output
  digitalWrite(Power, HIGH);   // Turn on the uSUP power

  Wire.begin(SDA, SCL);
 
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
