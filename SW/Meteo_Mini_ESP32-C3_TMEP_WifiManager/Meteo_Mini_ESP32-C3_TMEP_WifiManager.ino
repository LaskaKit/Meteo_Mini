/*
*  This is BETA version of versatile code used for TMEP.CZ(.EU) together with Meteo Mini ESP32-C3 and sensors.
*  Description: After the uploading, WiFi manager will create an AP 
*  and wait for WiFi SSID and PASSWORD.
*  Connect to this AP through smart phone or laptop. Also, you have to fill 
*  the TMEP.CZ(.EU) sensor address where you would like to send the data and deep-sleep time.
*
*  The FW will search the addresses of following sensors: SHT40, BME280 (0x77), SCD41, DS18B20
*  or you may force the sensor type and then the auto-search is disabled. 
*
*  Based on the searched sensor, the GET URL is filled as
*  SHT40: temperature + humidity + battery voltage; expected TMEP GUIDs are: temp, humV, voltage
*  BME280: temperature + humidity + pressure + battery voltage; expected TMEP GUIDs are: temp, humV, pressure, voltage
*  SCD41: temperature + humidity + CO2 + battery voltage; expected TMEP GUIDs are: temp, humV, co2, voltage
*  DS18B20: temperature + battery voltage; expected TMEP GUIDs are: temp, voltage
*  Connect only ONE sensor at the same time !!!
*
*  Libraries: 
*  https://github.com/Sensirion/arduino-i2c-sht4x
*  https://github.com/adafruit/Adafruit_BME280_Library
*  https://github.com/Sensirion/arduino-i2c-scd4x
*  https://github.com/tzapu/WiFiManager
*  https://github.com/milesburton/Arduino-Temperature-Control-Library
*  ESP library 2.0.17 https://github.com/espressif/arduino-esp32
*
*  Hardware:
*  https://www.laskakit.cz/laskakit-meteo-mini/?variantId=10473
*  https://www.laskakit.cz/laskakit-scd41-senzor-co2--teploty-a-vlhkosti-vzduchu/
*  https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/
*  https://www.laskakit.cz/arduino-senzor-tlaku--teploty-a-vlhkosti-bme280/
*  https://www.laskakit.cz/dallas-digitalni-vodotesne-cidlo-teploty-ds18b20-1m/
*
*  Written by laskakit.cz (2024)
*  
*/

#include <Arduino.h>
#include <SensirionI2CSht4x.h>
#include <Adafruit_BME280.h>
#include <SensirionI2CScd4x.h>
#include <Wire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <DNSServer.h>
#include <WebServer.h>
#include <EEPROM.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define version 0.1

// Data wire is connected to GPIO 10
#define ONE_WIRE_BUS 10

// Voltage divider for battery measurement
#define DIVIDER_RATIO 1.7693877551

// PWR PIN for uSup 
#define PWR_PIN 3

// ADC IN (battery voltage)
#define ADC_IN  0

// Create instance of WiFiManager
WiFiManager wm;

// Custom parameters
char serverAddress[40] = "XXXYYYZZZ.tmep.cz";
int sleepTime = 15; // Default sleep time in minutes
int sensorType = 99; // Default sensor type (0: SHT40, 1: BME280, 2: SCD41, 3: DS18B20)
//int heaterEn = 0; // Default heater setting (0: OFF, 1: ON)
//int heaterOnTime = 1; // Default heater setting for ON (in sec)
//int heaterOffTime = 2; // Default heater setting for OFF (in sec)

WiFiManagerParameter custom_serverAddress("server", "Server Address (max 40 chars)", serverAddress, 40);
WiFiManagerParameter custom_sleepTime("sleepTime", "Sleep Time (max 200 minutes)", String(sleepTime).c_str(), 6);
WiFiManagerParameter custom_sensorType("sensorType", "Sensor auto search (99: auto, 0: SHT40, 1: BME280, 2: SCD41, 3: DS18B20)", String(sensorType).c_str(), 2);
//WiFiManagerParameter custom_heaterEn("heaterEn", "SHT40 Heater setting (0: OFF, 1:ON)", String(heaterEn).c_str(), 1);
//WiFiManagerParameter custom_heaterOnTime("heaterOnTime", "Heater ON time (max 9 sec)", String(heaterOnTime).c_str(), 1);
//WiFiManagerParameter custom_heaterOffTime("heaterOffTime", "Heater OFF time (max 9 sec)", String(heaterOffTime).c_str(), 1);

SensirionI2CSht4x sht4x;
Adafruit_BME280 bme;
SensirionI2CScd4x scd4x;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature DS18B20(&oneWire);

// Variable to store the address of the DS18B20 sensor
DeviceAddress sensorAddress;

void saveConfigCallback() {
  Serial.println("Saving config...");
  strcpy(serverAddress, custom_serverAddress.getValue());
  sleepTime = atoi(custom_sleepTime.getValue());
  sensorType = atoi(custom_sensorType.getValue());
  //heaterEn = atoi(custom_heaterEn.getValue());
  //heaterOnTime = atoi(custom_heaterOnTime.getValue());
  //heaterOffTime = atoi(custom_heaterOffTime.getValue());

  EEPROM.put(0, serverAddress);
  EEPROM.put(40, sleepTime);
  EEPROM.put(50, sensorType);
  //EEPROM.put(41, heaterEn);
  //EEPROM.put(42, heaterOnTime);
  //EEPROM.put(43, heaterOffTime);
  EEPROM.commit();
}

void setup() 
{
  EEPROM.begin(512);

  pinMode(PWR_PIN, OUTPUT);    // Set uSUP connector power transistor as output
  digitalWrite(PWR_PIN, HIGH); // Turn power ON uSUP connector
  delay(100);            // Delay so it has time to turn on

  Serial.begin(115200);
  delay(100);

  Serial.println("-------------------");
  Serial.println("Laskakit Meteo Mini");
  Serial.println("TMEP and WiFi manager");
  Serial.println("supporting SHT40 or BME280 or SCD41 or DS18B20");
  Serial.println("depends on connected sensor (only ONE sensor)");
  Serial.print("version: "); Serial.println(version);
  Serial.println("-------------------");

  // Read stored configuration
  EEPROM.get(0, serverAddress);
  EEPROM.get(40, sleepTime);
  EEPROM.get(50, sensorType);
  //EEPROM.get(41, heaterEn);
  //EEPROM.get(42, heaterOnTime);
  //EEPROM.get(43, heaterOffTime);

  Serial.println("Stored Server Address: " + String(serverAddress));
  Serial.println("Stored Sleep Time: " + String(sleepTime));
  Serial.println("Auto Search Setting: " + String(sensorType));
  //Serial.println("Stored Heater Setting: " + String(heaterEn));
  //Serial.println("Stored Heater ON time: " + String(heaterOnTime));
  //Serial.println("Stored Heater OFF time: " + String(heaterOffTime));

  // Set custom parameters
  wm.addParameter(&custom_serverAddress);
  wm.addParameter(&custom_sleepTime);
  wm.addParameter(&custom_sensorType);
  //wm.addParameter(&custom_heaterEn);
  //wm.addParameter(&custom_heaterOnTime);
  //wm.addParameter(&custom_heaterOffTime);

  // Set save config callback
  wm.setSaveConfigCallback(saveConfigCallback);

  // Connect to WiFi
  if (!wm.autoConnect("Laskakit Meteo Mini config")) 
  {
    Serial.println("Failed to connect and hit timeout");

    // Sleep for the configured time if WiFi connection fails
    esp_sleep_enable_timer_wakeup(sleepTime * 60 * 1000000);
    esp_deep_sleep_start();
  }

  Serial.println("Connected to WiFi");

  // I2C
  Wire.begin(19, 18); //19 - SDA, 18 - SCL

  // OneWire
  DS18B20.begin(); // 10 - DATA

  uint16_t error;
  char errorMessage[256];

  /* SHT40 */
  if((sensorType == 0) || (sensorType == 99))
  {
    sht4x.begin(Wire);

    uint32_t serialNumber;
    error = sht4x.serialNumber(serialNumber);
    if (error) 
    {
      Serial.println("Could not find a valid SHT40 sensor, check wiring!");
    } 
    else 
    {
      Serial.println("SHT40 found");
      sensorType = 0;
    }
  }

  /* BME280 */
  if((sensorType == 1) || (sensorType == 99))
  {
    if (!bme.begin(0x77))
    {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
    }
    else
    {
      Serial.println("BME280 found");
      sensorType = 1;

      // bme setting
      bme.setSampling(Adafruit_BME280::MODE_FORCED, // Force reading after delayTime
                Adafruit_BME280::SAMPLING_X1, // Temperature sampling set to 1
                Adafruit_BME280::SAMPLING_X1, // Pressure sampling set to 1
                Adafruit_BME280::SAMPLING_X1, // Humidity sampling set to 1
                Adafruit_BME280::FILTER_OFF   // Filter off - immediate 100% step response
                );
    } 
  }

  
  /* SCD41 */
  if((sensorType == 2) || (sensorType == 99))
  {
    scd4x.begin(Wire);

    error = scd4x.startPeriodicMeasurement();
    if (error) 
    {
      Serial.println("Could not find a valid SCD41 sensor, check wiring!");
    }
    else
    {
      Serial.println("SCD41 found");
      sensorType = 2;
    }
  }


  /* DS18B20 */
  if((sensorType == 3) || (sensorType == 99))
  {
    // Check if any device is present on the OneWire bus
    if (!oneWire.search(sensorAddress)) 
    {
      Serial.println("Could not find a valid DS18B20 sensor, check wiring!");
      oneWire.reset_search();
    } 
    else 
    {
      Serial.println("DS18B20 found");
      sensorType = 3;
    }
  }

}

void loop() 
{
  uint16_t error;
  char errorMessage[256];

  float temperature = 0;
  float humidity;
  float pressure;
  uint16_t co2;
  float battery_voltage;

  battery_voltage = (analogReadMilliVolts(ADC_IN) * DIVIDER_RATIO / 1000);
  Serial.print("ADC in mV: "); Serial.println(analogReadMilliVolts(ADC_IN));

  if (sensorType == 0) // SHT40
  {
    /*if(heaterEn == 1)
    {
      Serial.println("SHT40: Turning heater ON");
      sht4x.heaterOn();
      // Wait, heaterONtime
      delay(heaterOnTime);
      // Turn heater off
      Serial.println("SHT40: Turning heater OFF");
      sht4x.heaterOff();
      delay(heaterOffTime);
    }*/
    error = sht4x.measureHighPrecision(temperature, humidity);
    if (error) 
    {
      Serial.print("Error trying to execute measureHighPrecision(): ");
      errorToString(error, errorMessage, 256);
      Serial.println(errorMessage);
      return;
    }
  } 
  else if (sensorType == 1) // BME280
  {
    temperature = bme.readTemperature();
    humidity = bme.readHumidity();
    pressure = bme.readPressure() / 100.0F;
  } 
  else if (sensorType == 2) // SCD41
  {
    delay(3000);
    error = scd4x.readMeasurement(co2, temperature, humidity);
    if (error) 
    {
      Serial.print("Error trying to execute readMeasurement(): ");
      errorToString(error, errorMessage, 256);
      Serial.println(errorMessage);
      return;
    }
  }
  else if(sensorType == 3) // DS18B20
  {
    // Request temperature readings
    DS18B20.requestTemperatures();
    // Fetch temperature in Celsius
    temperature = DS18B20.getTempC(sensorAddress);
  }

  /* Print to Serial Monitor */
  Serial.print("Temperature: ");
  Serial.print(temperature);

  if ((sensorType == 0) || (sensorType == 1) || (sensorType == 2))
  {
    Serial.print("\tHumidity: ");
    Serial.println(humidity);
  }
  if (sensorType == 1) 
  {
    Serial.print("\tPressure: ");
    Serial.println(pressure);
  } 
  if (sensorType == 2) 
  {
    Serial.print("\tCO2: ");
    Serial.println(co2);
  } 

  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http;
    /* Send to TMEP */
    String url = "http://" + String(serverAddress) + "/?temp=" + String(temperature);

    if ((sensorType == 0) || (sensorType == 1) || (sensorType == 2))
    {
      url += "&humV=" + String(humidity);
    } 
    if (sensorType == 1) 
    {
      url += "&pressV=" + String(pressure);
    } 
    if (sensorType == 2) 
    {
      url += "&CO2=" + String(co2);
    }
    url += "&voltage=" + String(battery_voltage);

    http.begin(url);
    Serial.println(url);
    int httpResponseCode = http.GET();
    if (httpResponseCode > 0) 
    {
      Serial.println("HTTP Response code: " + String(httpResponseCode));
    } 
    else 
    {
      Serial.println("Error in HTTP request");
    }
    http.end();
  } 
  else 
  {
    Serial.println("WiFi not connected");
  }

  Serial.println("Meteo Mini is going to sleep...");
  
  digitalWrite(PWR_PIN, LOW); // Turn power OFF uSUP connector
  Serial.flush();
  delay(100);

  // Sleep for the configured time
  esp_sleep_enable_timer_wakeup(sleepTime * 60 * 1000000);
  esp_deep_sleep_start();
}
