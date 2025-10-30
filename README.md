# LaskaKit Meteo Mini with ESP32-C3 — More Powerful and Energy Efficient

A weather station is one of the most popular projects among makers.  
Blinking an LED is fun at first, but it gets boring quickly.  
When you build your own weather station, it will serve you for a long time — the longer it runs, the better, as you’ll collect long-term statistics.  
And with your own station, you might even detect a volcanic eruption on the other side of the world (thanks to a pressure sensor recording the shockwave).

We know not everyone can or wants to design their own hardware, so we’re introducing our development board designed specifically (but not only) for weather stations — [**LaskaKit Meteo Mini**](https://www.laskakit.cz/laskakit-meteo-mini).

![LaskaKit Meteo Mini v4.1 and newer](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit-meteo-mini_v4-2.jpg)

This development board based on **ESP32-C3** (a major upgrade from the older, less efficient ESP12S/ESP8266 version) makes building your weather station easier.  
It includes everything you need to get started — and can be easily expanded with additional sensor modules.

---

## 🧩 Specifications

| Parameter | Value |
|------------|--------|
| **Board version** | v4.1 |
| **Microcontroller** | ESP32-C3-MINI (Wi-Fi, BLE, RISC-V core) |
| **USB input voltage** | 3.4–5.5 V |
| **Solar input voltage** | 5–10 V *(recommended 6 V solar panel)* |
| **Deep-sleep current consumption** | 23 μA |
| **Antenna connector (IPEX version)** | [IPEX3](https://www.laskakit.cz/vyhledavani/?string=IPEX3&lb.f%5B%5D=category%3AP%C5%99enos%20a%20ukl%C3%A1d%C3%A1n%C3%AD%20dat&lb.f%5B%5D=category%3APropojovac%C3%AD%20kabely) |
| **Power supply** | USB-C or single-cell Li-Ion battery |
| **Charging IC** | BQ24074RGTR with charging indicators *(LED CHG/POWER GOOD)*.NTC allows battery charging only within the safe temperature range of 0 °C to 50 °C. |
| **USB interface** | CH9102F |
| **Voltage regulators** | RT9080 (ESP), RT9080 (peripherals, IO4 → HIGH to enable) |
| **Dimensions** | 48.4 × 32.9 × 9 mm |
| **Weight** | 8 g |

---

## ⚙️ Board Pinout

On the front of the board, you’ll find the Wi-Fi module with ESP32-C3.  
It delivers higher performance than the older ESP8266 version and is much more energy-efficient — consuming only **23 μA** in deep-sleep mode.

The module supports **IEEE 802.11 b/g/n** Wi-Fi standards.  
The **CH_CURRENT** solder bridge allows you to set the maximum charging current for the battery: **1.0 A or 1.34 A**, depending on resistor configuration (see schematic).

The board can be powered off using the onboard power switch.  
On the right side, there’s a **USB-C connector** for charging and power input.  
At the bottom, you’ll find connectors for a **Li-Ion battery (Battery)** and a **solar panel (Solar)**.

On the right side, there’s also a **1-Wire interface** for the **DS18B20 temperature sensor** (GPIO10).  
On the left side, you’ll find a set of **µSup connectors** – our custom connector standard compatible with **SparkFun Qwiic** and **Adafruit STEMMA**.  
In addition to the standard **I2C µSup connector**, there are also **µSup SPI** and **µSup IO** connectors.

Power for the µSup connectors is controlled via **GPIO4 (HIGH = enabled)**, allowing for even lower power consumption.  
A 3.3 V voltage regulator is integrated directly on the board.  
Battery voltage is measured using a voltage divider (1 MΩ and 1.3 MΩ) connected to **IO0 (ADC input)**.

![LaskaKit Meteo Mini with ESP32-C3 pinout](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit-meteo-mini_v4-1.jpg)

---

## 🔌 Sensor Connections

| Interface | Connector | Signals |
|------------|------------|----------|
| **µSup I2C** | JST-SH 4-pin | SDA: IO19, SCL: IO18 |
| **µSup SPI** | JST-SH 6-pin | CS: IO3, MOSI: IO7, SCK: IO6, MISO: IO2 |
| **µSup IO** | 2× JST-SH 3-pin | IO1, IO10 *(supports DS18B20)* |

---

## ⚡ Battery and Solar Panel Connection

Power from USB-C and the solar panel is combined through protection diodes into the input of the **BQ24074** charging IC.  
Connecting both power sources simultaneously is safe.  
The **recommended solar panel** is 6 V, but **10 V panels can also be safely used**.  
Charging current is **configurable using the CH_CURRENT solder jumpers**: **0.5 A (default)**, **1.0 A**, or **1.34 A** *(when all three jumpers are bridged)*.  
Charging status is indicated by LEDs — **CHG** (charging) and **POWER GOOD** (fully charged).

---

## 🔋 Battery Voltage Measurement

The battery voltage (**VCC**) is connected through a resistor divider to the **IO0 (ADC)** input of the ESP32-C3 microcontroller.

---

## 💡 LEDs and Sensors

- **Addressable RGB LED:** SK6812-EC20 on IO9  
- **Button:** IO5 → pressed = LOW  
- **Temperature sensor:** NTC 10 kΩ (3435) – for battery temperature monitoring  

---

## 🧠 Programming

Install [ESP32-C3 support](https://github.com/espressif/arduino-esp32) in Arduino IDE.  
For versions **3.5 and newer** (including **v4.1**), **no external programmer** is required — the CH9102F interface is already integrated on the board.  
Older versions can use the [CH340C programmer](https://www.laskakit.cz/laskakit-ch340-programmer-usb-c--microusb--uart/).

---

## 💾 Example Code

Example code and libraries are available here:  
👉 [https://github.com/LaskaKit/Meteo_Mini/tree/main/SW/](https://github.com/LaskaKit/Meteo_Mini/tree/main/SW/)

---

## 📦 Availability

The board is available in two variants:  
- with an **integrated PCB antenna**  
- or with an **external antenna connector (IPEX3)**  

👉 [https://www.laskakit.cz/laskakit-meteo-mini/](https://www.laskakit.cz/laskakit-meteo-mini/)

---

## 🧱 3D Printed Case

A 3D-printable case model is available:

![LaskaKit Meteo Mini 3D case](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/laskakit-meteo-mini-meteostanice_v3-6.jpg)

And yes — **we actually use what we sell** (photo of an earlier version):

![LaskaKit Meteo Mini Weather Station](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit-laskakit-meteo-mini-meteostanice-v3-main-1.jpg)

---

## 🕹️ Older Board Version

### Meteo Mini v3.5
- **IO3** was used to enable peripherals (µSup connector power).  
- **Maximum solar panel input voltage:** 6 V.  
- Charging IC: **TP4054** – lower efficiency, no direct solar input support.  
- No µSup SPI or µSup IO connector.