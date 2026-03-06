/*
*  This is BETA version of versatile code used for TMEP.CZ(.EU) together with Meteo Mini ESP32-C3 and sensors.
*  Description: After the uploading, WiFi manager will create an AP 
*  and wait for WiFi SSID and PASSWORD.
*  Connect to this AP through smart phone or laptop. Also, you have to fill 
*  the TMEP.CZ(.EU) sensor address where you would like to send the data and deep-sleep time.
*
*  The FW will search the addresses of following sensors: SHT40 (0x44), SHT40 (0x45), BME280 (0x76), BME280 (0x77), SCD41, DS18B20
*  OR you may force the sensor type and then the auto-search is disabled. 
*
*  Based on the searched sensor, the GET URL is filled as
*  SHT40: temperature + humidity + battery voltage; expected TMEP GUIDs are: temp, humV, voltage
*  BME280: temperature + humidity + pressure + battery voltage; expected TMEP GUIDs are: temp, humV, pressure, voltage
*  SCD41: temperature + humidity + CO2 + battery voltage; expected TMEP GUIDs are: temp, humV, co2, voltage
*  DS18B20: temperature + battery voltage; expected TMEP GUIDs are: temp, voltage
*  Connect only ONE sensor at the same time !!!
*
*  Libraries: 
*  https://github.com/Sensirion/arduino-i2c-sht4x (tested 1.1.2)
*  https://github.com/adafruit/Adafruit_BME280_Library (tested 2.2.4)
*  https://github.com/Sensirion/arduino-i2c-scd4x (tested v0.4.0)
*  https://github.com/tzapu/WiFiManager (tested 2.0.17)
*  https://github.com/milesburton/Arduino-Temperature-Control-Library (tested 4.0.1)
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
#include <SensirionI2cSht4x.h>
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

#define version 0.2

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
int sensorType = 99; // Default sensor type (0: SHT40 (0x44), 1: SHT (0x45), 2: BME280 (0x76), 3: BME280 (0x77), 4: SCD41, 5: DS18B20)

WiFiManagerParameter custom_serverAddress("server", "Server Address (max 40 chars)", serverAddress, 40);
WiFiManagerParameter custom_sleepTime("sleepTime", "Sleep Time (max 200 minutes)", String(sleepTime).c_str(), 6);
WiFiManagerParameter custom_sensorType("sensorType", "Sensor auto search (99: auto, 0: SHT40 (0x44), 1: SHT40 (0x45), 2: BME280 (0x76), 3: BME280 (0x77), 4: SCD41, 5: DS18B20)", String(sensorType).c_str(), 2);

SensirionI2cSht4x sht4x;
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

  EEPROM.put(0, serverAddress);
  EEPROM.put(40, sleepTime);
  EEPROM.put(50, sensorType);
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
  Serial.println("supporting SHT40 (0x44, 0x45) or BME280 (0x76, 0x77) or SCD41 or DS18B20");
  Serial.println("depends on connected sensor (only ONE sensor)");
  Serial.print("version: "); Serial.println(version);
  Serial.println("-------------------");

  // Read stored configuration
  EEPROM.get(0, serverAddress);
  EEPROM.get(40, sleepTime);
  EEPROM.get(50, sensorType);

  Serial.println("Stored Server Address: " + String(serverAddress));
  Serial.println("Stored Sleep Time: " + String(sleepTime));
  Serial.println("Auto Search Setting: " + String(sensorType));

  // Set custom parameters
  wm.addParameter(&custom_serverAddress);
  wm.addParameter(&custom_sleepTime);
  wm.addParameter(&custom_sensorType);

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

  /* SHT40 - 0x44 */
  if((sensorType == 0) || (sensorType == 99))
  {
    sht4x.begin(Wire, 0x44); 

    uint32_t serialNumber;
    error = sht4x.serialNumber(serialNumber);
    if (error) 
    {
      Serial.println("Could not find a valid SHT40 sensor (0x44), check wiring!");
    } 
    else 
    {
      Serial.println("SHT40 found");
      sensorType = 0;
    }
  }

  /* SHT40 - 0x45 */
  if((sensorType == 1) || (sensorType == 99))
  {
    sht4x.begin(Wire, 0x45); 

    uint32_t serialNumber;
    error = sht4x.serialNumber(serialNumber);
    if (error) 
    {
      Serial.println("Could not find a valid SHT40 sensor (0x45), check wiring!");
    } 
    else 
    {
      Serial.println("SHT40 found");
      sensorType = 1;
    }
  }

  /* BME280 - 0x76 */
  if((sensorType == 2) || (sensorType == 99))
  {
    if (!bme.begin(0x76))
    {
      Serial.println("Could not find a valid BME280 sensor (0x76), check wiring!");
    }
    else
    {
      Serial.println("BME280 found");
      sensorType = 2;

      // bme setting
      bme.setSampling(Adafruit_BME280::MODE_FORCED, // Force reading after delayTime
                Adafruit_BME280::SAMPLING_X1, // Temperature sampling set to 1
                Adafruit_BME280::SAMPLING_X1, // Pressure sampling set to 1
                Adafruit_BME280::SAMPLING_X1, // Humidity sampling set to 1
                Adafruit_BME280::FILTER_OFF   // Filter off - immediate 100% step response
                );
    } 
  }
  /* BME280 - 0x77 */
  if((sensorType == 3) || (sensorType == 99))
  {
    if (!bme.begin(0x77))
    {
      Serial.println("Could not find a valid BME280 sensor (0x77), check wiring!");
    }
    else
    {
      Serial.println("BME280 found");
      sensorType = 3;

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
  if((sensorType == 4) || (sensorType == 99))
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
      sensorType = 4;
    }
  }


  /* DS18B20 */
  if((sensorType == 5) || (sensorType == 99))
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
      sensorType = 5;
    }
  }

}

void loop() 
{
  uint16_t error;
  char errorMessage[256];

  float temperature = 0;
  float humidity = 0;
  float pressure = 0;
  uint16_t co2 = 0;
  float battery_voltage = 0;

  battery_voltage = (analogReadMilliVolts(ADC_IN) * DIVIDER_RATIO / 1000);
  Serial.print("ADC in mV: "); Serial.println(analogReadMilliVolts(ADC_IN));

  delay(100);

  if ((sensorType == 0) || (sensorType == 1)) // SHT40 0x44 or 0x45
  {
    error = sht4x.measureHighPrecision(temperature, humidity);
    if (error) 
    {
      Serial.print("Error trying to execute measureHighPrecision(): ");
      errorToString(error, errorMessage, 256);
      Serial.println(errorMessage);
      return;
    }
  } 
  else if ((sensorType == 2) || (sensorType == 3)) // BME280 0x76 or 0x77
  {
    temperature = bme.readTemperature();
    humidity = bme.readHumidity();
    pressure = bme.readPressure() / 100.0F;
  } 
  else if (sensorType == 4) // SCD41
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
  else if(sensorType == 5) // DS18B20
  {
    // Request temperature readings
    DS18B20.requestTemperatures();
    // Fetch temperature in Celsius
    temperature = DS18B20.getTempC(sensorAddress);
  }

  /* Print to Serial Monitor */
  Serial.print("Temperature: ");
  Serial.print(temperature);

  if ((sensorType == 0) || (sensorType == 1) || (sensorType == 2) || (sensorType == 3) || (sensorType == 4))
  {
    Serial.print("\nHumidity: ");
    Serial.println(humidity);
  }
  if ((sensorType == 2) || (sensorType == 3))
  {
    Serial.print("\nPressure: ");
    Serial.println(pressure);
  } 
  if (sensorType == 4) 
  {
    Serial.print("\nCO2: ");
    Serial.println(co2);
  } 

  if (WiFi.status() == WL_CONNECTED) 
  {
    HTTPClient http;
    /* Send to TMEP */
    String url = "http://" + String(serverAddress) + "/?temp=" + String(temperature);

    if ((sensorType == 0) || (sensorType == 1) || (sensorType == 2) || (sensorType == 3) || (sensorType == 4))
    {
      url += "&humV=" + String(humidity);
    } 
    if ((sensorType == 2) || (sensorType == 3))
    {
      url += "&pressV=" + String(pressure);
    } 
    if (sensorType == 4) 
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

  Serial.print("Meteo Mini is going to sleep for "); 
  Serial.print(sleepTime); 
  Serial.println(" minutes");
  
  digitalWrite(PWR_PIN, LOW); // Turn power OFF uSUP connector
  Serial.flush();
  delay(100);

  // Sleep for the configured time
  esp_sleep_enable_timer_wakeup(sleepTime * 60 * 1000000);
  esp_deep_sleep_start();
}
