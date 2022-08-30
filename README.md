# LaskaKit Meteo Mini with ESP32-C3. More powerful and low-power. 
The weather station is one of the famous project which makers are looking for.</br>
Of course, you can blink with LED, it is nice start, but after ten blinks it is boring. If you make an weather station, you will be satisfied with yourself because when it is working longer, you have better results and charts of measuring of temperature, humidity, pressure... whatever. </br>
We know not all of makers are able to design a board, so we are comming with our weather station board called [LaskaKit Meteo Mini](https://www.laskarduino.cz/laskakit-meteo-mini).</br>

![LaskaKit Meteo Mini with ESP32-C3](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/1.jpg)

This evaluation board which includes Wi-Fi module ESP32-C3 should help you to speed up the development of your project. It contains everything what you need.</br>
Is there something missing? No problem, you can adjust the board by extension modules, because Meteo Mini includes μŠup connector where you can connect a lot of sensors.</br>

## Pinout

On the TOP side, you see the Wi-Fi module with ESP32-C3. 
This Wi-Fi module supports IEEE 802.11 b/g/n. Two buttons (FLASH and RESET), soldering bridge the choose of charging current to battery.</br>
The board may be completely off thanks to switch on the left side on the board. On the right side, you may see the USB-C (not microUSB ;-) ) connector used only charging of Li-ion battery. As you can see, there are two 2-pins connectors, one is used for Li-ion battery (BATTERY) and second one is used for solar panel (SOLAR).
There is also 1-wire bus which you can connect the board with temperature sensor DS18B20. On the left side is our already mentioned μŠup connector. You can easily and quicly connect [SHT40 (temperature/humidity)](https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/) and [SCD41 (temperature/humidity/CO2)](https://www.laskakit.cz/laskakit-scd41-senzor-co2--teploty-a-vlhkosti-vzduchu/).

The Meteo Mini includes voltage divider what is used for measuring of battery voltage. The battery voltage is conencted through voltage divider (R6=1M; R7=1.3M) to IO0 of ESP32-3.</br>
The connector on the bottom side is used for programming of ESP32-C3.

The power consumption of Meteo Mini is only 8 uA, what is 4x less than the previous version with ESP8266.

## Programming

Install the [ESP8266 package](https://github.com/espressif/arduino-esp32) in Arduino IDE.
Then just use our [programmer with CH340C](https://www.laskakit.cz/laskakit-ch340-programmer-usb-c--microusb--uart/). Just plug in the programmer to Meteo Mini and switch the voltage level on programmer to 3.3V. 

## Power supply 

The solar pannel and USB-C connector are connected to charing IC through shottky diodes which are protecting the solar panel and USB-C connector in case you connect both power suppllies to the charging IC (TP4054).
The charging current may be up to 400 mA (default) or 280 mA. Depeding on CH-CURRENT solder bridge. The maximum input voltage is 9V, so be careful in case the Li-ion is fully charged and sun is shining on solar panel, then the voltage on solar panel is higher than nominal value. We recommend 6V solar panel. 

## Voltage of Li-ion battery
VCC (battery voltage) is connected through voltage divider to ADC of ESP32-C3, IO0.
The maximum voltage of ADC is 3.3V.

## Example code
We wrote an example code to understand how you can use Meteo Mini board. The sample is available on https://github.com/LaskaKit/Meteo_Mini/tree/main/SW/

You can buy assembled board which is available on https://www.laskakit.cz/laskakit-meteo-mini

We also provide 3D file for case which you can print on 3D printer...

![LaskaKit Meteo Mini 3D case](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini_3Dcase.jpg)

... and we are really using this Meteo Mini as a weather station with solar panel (previous version).

![LaskaKit Meteo Mini Weather Station](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini_weatherstation.jpg)

