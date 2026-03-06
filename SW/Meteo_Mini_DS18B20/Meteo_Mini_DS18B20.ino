/*
* Example code for DS18B20 and MeteoMini board with ESP32-C3/C6
* Values are sent to Serial Monitor
*
* Board:   LaskaKit Meteo Mini C3                                 https://www.laskakit.cz/laskakit-meteo-mini/
*          LaskaKit Meteo Mini C6                               
* Sensor:  Maxim Integrated DS18B20+ digital temperature sensor   https://www.laskakit.cz/dallas-ds18b20--orig--digitalni-cidlo-teploty-to-92/
*
* Library:  https://github.com/milesburton/Arduino-Temperature-Control-Library
*           https://github.com/PaulStoffregen/OneWire
* 
* Made by laskakit.cz (c) 2026
*/


#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//#define Meteo_Mini_C3
#define Meteo_Mini_C6

#if defined(Meteo_Mini_C3)

  #define Power   4
  #define ONE_WIRE_BUS 10

#elif defined(Meteo_Mini_C6)

  #define Power   1
  #define ONE_WIRE_BUS 21

#endif

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

 
void setup() {
  Serial.begin(115200);
  while (!Serial) 
  {
    ; // cekani na Serial port
  }

  // for version over 3.5 need to turn uSUP ON
  pinMode(Power, OUTPUT);      // Set EN pin for uSUP stabilisator as output
  digitalWrite(Power, HIGH);   // Turn on the uSUP power

  sensors.begin();
}
 
/*
 * Main function, get and show the temperature
 */
void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  delay(1500);
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempCByIndex(0);

  // Check if reading was successful
  if (tempC != DEVICE_DISCONNECTED_C)
  {
    Serial.print("Temperature for the device 1 (index 0) is: ");
    Serial.println(tempC);
  }
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
}
