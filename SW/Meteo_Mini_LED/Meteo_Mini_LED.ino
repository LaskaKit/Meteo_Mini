/*
 * Example code for installed LED and Meteo Mini board with ESP32-C3/C6
 * LaskaKit LaskaKit Meteo Mini just changing LED color 
 * 
 * Board:   LaskaKit Meteo Mini C3      https://www.laskakit.cz/laskakit-meteo-mini/
 *          LaskaKit Meteo Mini C6      
 * 
 * 
 * Library:
 * https://github.com/adafruit/Adafruit_NeoPixel
 *
 * 
 * Made by laskakit.cz (c) 2026
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
