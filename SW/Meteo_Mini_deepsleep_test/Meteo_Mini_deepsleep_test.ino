
/*
* LaskaKit Meteo Mini boards deepsleep test
* 
* Board:   LaskaKit Meteo Mini C3      https://www.laskakit.cz/laskakit-meteo-mini/
*          LaskaKit Meteo Mini C6      
* 
* ! Must be disabled USB CDC On Boot
*
* Made by laskakit.cz (c) 2026
*/

// 

//#define Meteo_Mini_C3
#define Meteo_Mini_C6

#define SLEEP_SEC 65

#if defined(Meteo_Mini_C3)

  #define Power  4

#elif defined(Meteo_Mini_C6)

  #define Power  1

#endif

void setup(void)
{
  Serial.begin(115200);
  pinMode(Power, OUTPUT); 
  digitalWrite(Power, HIGH); // enable power supply for ePaper and uSup
  delay(500);

  goToSleep();
}

void loop(void) 
{

}

void goToSleep(){

  Serial.println("I'm mot sleeping");
  delay(1000);
  Serial.println("going to sleep 15 sek");
  digitalWrite(Power, LOW); // disable power supply for ePaper
  // ESP Deep Sleep 
  Serial.println("ESP in sleep mode");
  Serial.flush(); 
  esp_sleep_enable_timer_wakeup(SLEEP_SEC * 1000000);
  delay(200);
  esp_deep_sleep_start();
}
