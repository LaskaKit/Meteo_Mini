/*
* This example code is used for LaskaKit LaskaKit Meteo Mini v4.0 board  https://www.laskakit.cz/laskakit-meteo-mini/
* LaskaKit LaskaKit Meteo Mini just changing LED color 
* 
* Made by (c) laskakit.cz 2025
* 
*/

#include <Adafruit_NeoPixel.h>

//#define Meteo_Mini_C3
#define Meteo_Mini_C6

#if defined(Meteo_Mini_C3)

  #define Power 4
  #define LED   9

#elif defined(Meteo_Mini_C6)

  #define Power 1
  #define LED   9

#endif


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, LED, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pinMode(Power, OUTPUT);      // Set EN pin for second stabilisator as output
  digitalWrite(Power, HIGH);   // Turn on the second stabilisator

  pixels.begin();
  pixels.setBrightness(10);
}

void loop() {
     
  pixels.setPixelColor(0, pixels.Color(255, 0, 0)); // R, G, B
  pixels.show();

  delay(1000);

  pixels.setPixelColor(0, pixels.Color(0, 255, 0)); // R, G, B
  pixels.show();

  delay(1000);

  pixels.setPixelColor(0, pixels.Color(0, 0, 255)); // R, G, B
  pixels.show();

  delay(1000);

  pixels.setPixelColor(0, pixels.Color(255, 255, 255)); // R, G, B
  pixels.show();

  delay(1000);

}
