/* LasKKit DIY Mini Weather Station. 
 * Thingspeak edition
 * Read Temperature, Humidity and pressure and send to Thingspeak
 * For settings see settings.h
 * 
 * Email:obchod@laskarduino.cz
 * Web:laskarduino.cz

 * Adafruit BME280 library
 * https://github.com/adafruit/Adafruit_BME280_Library
 * Miles Burton DS18B20 library
 * https://github.com/milesburton/Arduino-Temperature-Control-Library
 */

// připojení knihoven
#include <Arduino.h>
#include "config_my.h"        // change to config.h and fill the file.

#include <Wire.h>
#include <OneWire.h>
#include <ESP8266WiFi.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <DallasTemperature.h>

//TODO add SHT10x 
#ifdef DALLAS
#define DSPIN D4
#endif

#define BME280_ADDRESS (0x76)   // (0x77) cut left and solder right pad on board
#define OFFSET 0.00             // offset pro mereni napeti baterie
#define SLEEP_SEC 15*60         // Measurement interval (seconds)

//IPAddress ip(192,168,1,50);       // pick your own IP outside the DHCP range of your router
//IPAddress gateway(192,168,1,1);   // watch out, these are comma's not dots
//IPAddress subnet(255,255,255,0);

const char* server = "api.thingspeak.com";

// Vytvoření instance | Instance creation
OneWire oneWireDS(DSPIN);
DallasTemperature dallas(&oneWireDS);
Adafruit_BME280 bme;
WiFiClient client;

float temperature;
float pressure;
float humidity;
float volt;
float temp_in;

void postData(){
  // Odesíláni dat do ThingSpeak | Post data to ThingSpeak
  if (client.connect(server,80)) {
    Serial.println("Connect to ThingSpeak - OK"); 
    
    String dataToThingSpeak = "";
    dataToThingSpeak+="GET /update?api_key=";
    dataToThingSpeak+=api_key;
    
    dataToThingSpeak+= "&field1=";
    dataToThingSpeak+= String(temperature);
    
    dataToThingSpeak+= "&field2=";
    dataToThingSpeak+= String(pressure);
    
    dataToThingSpeak+= "&field3=";
    dataToThingSpeak+= String(humidity);
    
    dataToThingSpeak+= "&field4=";
    dataToThingSpeak+= String(volt);
    
    dataToThingSpeak+="&field5=";
    dataToThingSpeak+=String(temp_in);
    
    dataToThingSpeak+=" HTTP/1.1\r\nHost: a.c.d\r\nConnection: close\r\n\r\n";
    dataToThingSpeak+="";
    Serial.println("posting data to ThingSpeak");
    Serial.println(dataToThingSpeak);
    client.print(dataToThingSpeak);
    
    int timeout = millis() + 5000;
    while (client.available() == 0) {
      if (timeout - millis() < 0) {
        Serial.println("Error: Client Timeout!");
        client.stop();
        return;
      }
    }
  } else Serial.println("Connect to ThingSpeak - FALSE"); 
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
}

// pripojeni k WiFi | WiFi Connection
void WiFiConnection(){
  Serial.println();
  Serial.print("Connecting to...");
  Serial.println(ssid);

 // WiFi.config(ip,gateway,subnet);   // Použít statickou IP adresu, config.h | Use static ip address, see config.h
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected successfully");
}

// Přečíst data z BME280 | Read data from BME280
void readBME(){
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;  
  
  Serial.print("Temp: "); Serial.print(temperature); Serial.println("°C");
  Serial.print("Humidity: "); Serial.print(humidity); Serial.println("% RH");
  Serial.print("Pressure: "); Serial.print(pressure); Serial.println("hPa");
}

// Přečíst data z DS18B20 | Read data from DS18B20
void readDallas(){
  dallas.requestTemperatures();
  temp_in = dallas.getTempCByIndex(0);  // (0) - pořadí dle unikátní adresy čidel | Fetch temperature for device index
  
  Serial.print("Temp_in: "); Serial.print(temp_in); Serial.println(" °C");
}

// Měření napětí baterie | Battery voltage measurement
void readBat(){
  int voltraw = system_adc_read();
  volt = voltraw / 1024.0 * 4.20;
  volt = OFFSET + volt;
 
  Serial.print("Napětí baterii: "); Serial.print(volt); Serial.println(" V");
}

void setup() {
  // Hned vypneme WiFi | disable WiFi, coming from DeepSleep, as we do not need it right away
  WiFi.mode( WIFI_OFF );
  WiFi.forceSleepBegin();
  delay( 1 );

  Serial.begin(115200);
  while(!Serial) {} // Wait
  
  pinMode(A0, INPUT);

  // initilizace BME280 | BME280 Initialization
  Wire.begin();
  if (! bme.begin(BME280_ADDRESS)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
  Serial.println("-- Weather Station Scenario --");
  Serial.println("forced mode, 1x temperature / 1x humidity / 1x pressure oversampling,");
  Serial.println("filter off");
  bme.setSampling(Adafruit_BME280::MODE_FORCED,
                  Adafruit_BME280::SAMPLING_X1, // temperature
                  Adafruit_BME280::SAMPLING_X1, // pressure
                  Adafruit_BME280::SAMPLING_X1, // humidity
                  Adafruit_BME280::FILTER_OFF   );

  // initilizace DS18B20 | DS18B20 Initialization
  dallas.begin();
  delay(10);

  readBME();
  readDallas();

  // Probudit WiFi | Wake up WiFi Modem
  WiFi.forceSleepWake();
  delay( 1 );
  WiFi.mode( WIFI_STA );
  
  // Pripojeni k WiFi | Connect to WiFi
  WiFiConnection();
  
  readBat();      // WiFi should be ON for ADC functionality, overwise getting 1024 reading.
  postData();

  WiFi.disconnect(true);
  delay(1);
  // ESP Deep Sleep 
  // Radio po probuzeni bude vypnuto | Radio disabled after wake up
  Serial.println("ESP8266 in sleep mode");
  ESP.deepSleep(SLEEP_SEC * 1000000, WAKE_RF_DISABLED); 
}

void loop(){
  // Nepotřebujeme loop | We dont use the loop
}