/*
* Test code for MeteoMini board with ESP32-C3/C6
* Test WiFi connection with WiFi Manager
*
* Board:   LaskaKit Meteo Mini C3      https://www.laskakit.cz/laskakit-meteo-mini/
*          LaskaKit Meteo Mini C6      
*
* Library:  https://github.com/tzapu/WiFiManager
*
* 
* Made by laskakit.cz (c) 2026
*/
 
#include <WiFi.h>
#include <WiFiManager.h>   // 
#include <HTTPClient.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println();
  Serial.println("=== ESP32 WiFi test ===");

  WiFi.mode(WIFI_STA);

  WiFiManager wm;

  // Volitelně: timeout pro konfigurační portál
  wm.setConfigPortalTimeout(180);

  // Pokus o připojení, pokud nejsou uložené údaje, otevře AP
  // Název AP: ESP32-WIFI-TEST
  bool res = wm.autoConnect("ESP32-WIFI-TEST");

  if (!res) {
    Serial.println("Nepodarilo se pripojit k WiFi.");
    Serial.println("Restartuji za 5 sekund...");
    delay(5000);
    ESP.restart();
  }

  Serial.println("WiFi pripojena.");
  Serial.print("IP adresa: ");
  Serial.println(WiFi.localIP());

  // Test stazeni stranky
  HTTPClient http;

  Serial.println("Stahuji https://www.laskakit.cz/ ...");

  http.begin("https://www.laskakit.cz/");
  int httpCode = http.GET();

  if (httpCode > 0) {
    Serial.print("HTTP kod: ");
    Serial.println(httpCode);

    String payload = http.getString();

    Serial.println("=== Zacatek odpovedi ===");
    if (payload.length() > 500) {
      Serial.println(payload.substring(0, 500));
    } else {
      Serial.println(payload);
    }
    Serial.println("=== Konec ukazky odpovedi ===");
  } else {
    Serial.print("Chyba HTTP pozadavku: ");
    Serial.println(http.errorToString(httpCode));
  }

  http.end();

  // Odpojeni od WiFi
  Serial.println("Odpojuji WiFi...");
  WiFi.disconnect(true, true);
  WiFi.mode(WIFI_OFF);

  Serial.println("WiFi odpojena.");
}

void loop() {
  // Nic dalsiho neni potreba
}