# LaskaKit Meteo Mini with ESP32-C3 — more powerful and energy-efficient

A weather station is one of the most popular projects among makers.  
Blinking an LED is a nice start, but it gets boring after a while.  
Building your own weather station, however, is a long-term project — the longer it runs, the more valuable your data becomes.  
And who knows — your own station might even detect a volcanic eruption on the other side of the planet (thanks to the pressure sensor recording the shockwave).

We know not everyone can or wants to design their own hardware, so we’re introducing our development board designed specifically (but not only) for weather stations — [**LaskaKit Meteo Mini**](https://www.laskakit.cz/laskakit-meteo-mini).

![LaskaKit Meteo Mini](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/1.jpg)  
![LaskaKit Meteo Mini v3.5 and newer](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini-C3_v3.5_1.JPG)

This development board based on **ESP32-C3** (a major upgrade from the older, less efficient ESP12S/ESP8266 version) makes building your weather station much easier.  
It includes everything you need to start and can be easily expanded with many other sensor modules.

---

## 🧩 Specifications

| Parameter | Value |
|------------|--------|
| **Board version** | v4.1 |
| **Microcontroller** | ESP32-C3-MINI (Wi-Fi, BLE, RISC-V core) |
| **USB input voltage** | 3.4–5.5 V |
| **Solar input voltage** | 5–10 V *(recommended 6 V solar panel)* |
| **Current draw in deep-sleep mode** | 23 μA |
| **Antenna connector (IPEX version)** | [IPEX3](https://www.laskakit.cz/vyhledavani/?string=IPEX3&lb.f%5B%5D=category%3AP%C5%99enos%20a%20ukl%C3%A1d%C3%A1n%C3%AD%20dat&lb.f%5B%5D=category%3APropojovac%C3%AD%20kabely) |
| **Power supply** | USB-C or single-cell Li-Ion battery |
| **Charging IC** | BQ24074RGTR with charging indication *(LED CHG/DONE)* |
| **USB interface** | CH9102F |
| **Voltage regulators** | RT9080 (ESP), RT9080 (peripherals, IO4 → HIGH to enable) |
| **Dimensions** | 48.4 × 32.9 × 9 mm |
| **Weight** | 8 g |

---

## ⚙️ Board pinout

On the front side, you’ll find the Wi-Fi module with ESP32-C3.  
It offers higher performance than older ESP8266-based versions and is far more power-efficient — consuming only **23 μA** in deep-sleep mode.

The module supports the **IEEE 802.11 b/g/n** standard.  
There are two buttons for uploading code — **FLASH** and **RESET**.  
The **CH_CURRENT** solder jumper allows you to set the maximum charging current for the battery: **1.0 A or 1.34 A**, depending on the resistor configuration (see schematic).

The board can be turned off using the power switch on the left side.  
On the right, there’s a **USB-C connector** for power and battery charging.  
On the bottom, you’ll find connectors for the **Li-Ion battery (Battery)** and **solar panel (Solar)**.

On the right side, there’s also a **1-Wire interface** for the **DS18B20 temperature sensor** (GPIO10).  
On the left, there’s a set of **µŠup connectors** — our own standard compatible with **SparkFun Qwiic** and **Adafruit STEMMA**.  
Besides the standard **µŠup I2C connector**, the board also features **µŠup SPI** and **µŠup IO** connectors.

Power to the µŠup connectors is controlled via **GPIO4 (HIGH = enabled)**, allowing even lower power consumption.  
A 3.3 V regulator is integrated directly on the board.  
For battery voltage monitoring, a voltage divider (1 MΩ and 1.3 MΩ) is connected to **IO0 (ADC input)**.

![LaskaKit Meteo Mini ESP32-C3 pinout](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini_ESP32-C3_pin.jpg)  
![LaskaKit Meteo Mini ESP32-C3 v3.5 and newer pinout](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini-C3_v3.5_pinout.JPG)

---

## 🔌 Sensor connections

| Interface | Connector | Signals |
|------------|------------|----------|
| **µŠup I2C** | JST-SH 4-pin | SDA: IO19, SCL: IO18 |
| **µŠup SPI** | JST-SH 6-pin | CS: IO3, MOSI: IO7, SCK: IO6, MISO: IO2 |
| **µŠup IO** | 2× JST-SH 3-pin | IO1, IO10 *(supports DS18B20)* |

---

## ⚡ Battery and solar panel connection

Power from the USB-C connector and solar panel is combined through protection diodes into the input of the **BQ24074** charging IC.  
Simultaneous connection of both power sources is therefore safe.  
The **recommended solar panel** is 6 V, but **10 V panels can also be safely used**.  
Charging current is **configurable using CH_CURRENT solder jumpers**: **0.5 A (default)**, **1.0 A**, or **1.34 A** *(when all three jumpers are bridged)*.  
Charging status is indicated by LEDs — **CHG** (charging) and **DONE** (fully charged).

---

## 🔋 Battery voltage measurement

Battery voltage (**VCC**) is connected through a voltage divider to the **IO0 (ADC)** input of the ESP32-C3 microcontroller.

---

## 💡 LEDs and sensors

- **Addressable RGB LED:** SK6812-EC20 on IO9  
- **Button:** IO5 → pressed = LOW  
- **Temperature sensor:** NTC 10 kΩ (3435) – for battery temperature monitoring  

---

## 🧠 Programming

Install [ESP32-C3 support](https://github.com/espressif/arduino-esp32) in Arduino IDE.  
For versions **3.5 and newer** (including **v4.1**), **no external programmer** is required — the CH9102F interface is already integrated on the board.  
Older versions can use the [CH340C programmer](https://www.laskakit.cz/laskakit-ch340-programmer-usb-c--microusb--uart/).

---

## 💾 Example code

Example code and libraries are available at:  
👉 [https://github.com/LaskaKit/Meteo_Mini/tree/main/SW/](https://github.com/LaskaKit/Meteo_Mini/tree/main/SW/)

---

## 📦 Availability

The board is available in two variants:  
- with an **integrated PCB antenna**  
- or with an **external antenna connector (IPEX3)**  

👉 [https://www.laskakit.cz/laskakit-meteo-mini/](https://www.laskakit.cz/laskakit-meteo-mini/)

---

## 🧱 Enclosure and 3D printing

A 3D-printable case model is available:

![LaskaKit Meteo Mini 3D case](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini_3Dcase.jpg)

And yes — **we actually use what we sell** (photo of an earlier version):

![LaskaKit Meteo Mini Weather Station](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini_weatherstation.jpg)