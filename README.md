# LaskaKit Meteo Mini
The weather station is one of the famous project which makers are looking for.
Of course, you can blink with LED, it is nice start, but after ten blinks it is boring. If you make an weather station, you will be satisfied with yourself because when it is working longer, you have better results and charts of measuring of temperature, humidity, pressure... whatever. 
We know not all of makers are able to design an board, so we are comming with our weather station board called [LaskaKit Meteo Mini](https://www.laskarduino.cz/laskakit-meteo-mini
).

![LaskaKit Meteo Mini](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini.jpg)

This evaluation board which includes Wi-Fi module ESP8266 should help you to speed up the development of your project. It contains everything what you need.
Is there something missing? No problem, we can adjust the board by extension modules, because Meteo Mini contains connectors which are pin-to-pin compatible with Wemos D1 Mini which isn't so low power as our board.

## Pinout

![LaskaKit Meteo Mini TOP](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_pinout_top.jpg)

On the TOP side, you see the Wi-Fi module ESP-12S with ESP8266. 
This Wi-Fi module supports IEEE 802.11 b/g/n. You can see Wemos D1 mini connectors for extension boards, two buttons (FLASH and RESET), soldering bridge for enabling of deep-sleep mode - if you solder it, you connect RESET with GPIO16 what is the output of the timer which is generaly used for wake-up. 
The board may be completely off thanks to switch on the left side on board. On the right side, you see microUSB connector used only charging of Li-ion battery. As you can see, there are two 2-pins connector, one is used for connecting of Li-ion battery (BATTERY) and second one is used for solar panel (SOLAR).
There is also 1-wire bus which you can connect the board with temperature sensor DS18B20.

![LaskaKit Meteo Mini BOTTOM](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_pinout_bottom.jpg)

On the bottom side, there is 4pin connector where is I2C bus. This connector may be used for another sensors like temperature sensor, humidity sensors, CO2 sensors and another. The conenctor includes power supply - 3.3V.
The Meteo Mini has voltage divider which is used for measuring of battery voltage - solder the soldering bridge called ADC. Keep in mind, the maximum voltage on ADC is 1V!
The connector on the bottom side is used for programming of ESP8266, there is RX, TX and power supply (+5V, GND).

Thanks the compatibility with Wemos D1 Mini, you can use the extension boards like [microSD slot](https://www.laskarduino.cz/wemos-d1-mini-microsd-shield/), temperature and humidity sensor [DHT11](https://www.laskarduino.cz/wemos-d1-mini-dht11-shield/)/[DHT22](https://www.laskarduino.cz/wemos-d1-mini-dht22-shield/), [SHT30](https://www.laskarduino.cz/wemos-d1-mini-sht30-shield--i2c/), [BMP180](https://www.laskarduino.cz/wemos-d1-mini-bmp180-shield/) or [OLED](https://www.laskarduino.cz/wemos-d1-mini-64x48-oled-displej-shield--i2c/).

All extension board you can find on this like [https://www.laskarduino.cz/esp-a-wemos/](https://www.laskarduino.cz/esp-a-wemos/)

![LaskaKit Meteo Mini Wemos](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_pinout_wemos.jpg)

## Programming

Install the ESP8266 package in Arduino IDE.

![LaskaKit Meteo Mini Arduino IDE](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_Generic_ESP8266_Module.png)
https://arduino.esp8266.com/stable/package_esp8266com_index.json

![LaskaKit Meteo Mini Arduino IDE Preference](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_Preference.jpg)

Before the uploading of your code, you have to switch the ESP8266 to boot mode, for this you will use the buttons RESET and FLASH.

Press the "FLASH" button and hold

Press "RESET" button and still hold "FLASH" button

Release the "RESET" button and after that also "FLASH" button

Click on Upload button in Arduino IDE

After the uploading of code, reset the board by pressing of RESET button

![LaskaKit Meteo Mini Programming](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini.gif)

## Connection of Li-ion battery and solar panel

![LaskaKit Meteo Mini Solar and MicroUSB](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_Solar.jpg)

The solar pannel and microUSB connector are connected to charing IC through shottky diodes which are protecting the solar panel and microUSB connector in case you connect both power suppllies. Then the current is connected to charging IC TP4054.
The charging current may be up to 800 mA. The maximum input voltage is 9V, so be careful in case the Li-ion is fully charged and sun is shining on solar panel, then the voltage on solar panel is higher than nominal value. We recommend 6V solar panel. 
The charging current is defined by R11 (Rprog).

![LaskaKit Meteo Mini ADC formula](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_ADC_formula.jpg)

## Voltage of Li-ion battery
VCC (battery voltage) is connected through voltage divider to ADC of ESP8266.
The maximum voltage of ADC is 1V.

![LaskaKit Meteo Mini ADC](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_ADC.jpg)

## Example code
We wrote an example code to understand how you can use Meteo Mini board. The sample is available on https://github.com/LaskaKit/Weather_Station_Mini

Meteo Mini reads the temperature, humidity and pressure from sensors and sends data to Thingspeak.

You can buy assembled board which is available on https://www.laskarduino.cz/laskakit-meteo-mini

