# LaskaKit Meteo Mini s ESP32-C3 — výkonnější a úspornější

Meteostanice je jeden z projektů, které bastlíři nejčastěji vyhledávají.  
Když si blikáš LEDkou, je to sice pěkné, ale za chvíli tě to asi omrzí.  
Když si postavíš meteostanici, bude ti sloužit dlouho — vlastně čím déle, tím lépe, protože budeš mít dlouhodobé statistiky.  
A třeba díky vlastní meteostanici dokážeš zachytit výbuch sopky na druhé straně zeměkoule (díky čidlu tlaku, které zaznamená tlakovou vlnu).

Víme, že každý si nedokáže nebo nechce navrhnout vlastní hardware, a tak přicházíme s naší vývojovou deskou určenou (nejen) pro meteostanice — [**LaskaKit Meteo Mini**](https://www.laskakit.cz/laskakit-meteo-mini).

![LaskaKit Meteo Mini](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/1.jpg)  
![LaskaKit Meteo Mini v3.5 a novější](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini-C3_v3.5_1.JPG)

Tato vývojová deska s **ESP32-C3** (což je výrazná změna oproti starší méně úsporné verzi s ESP12S/ESP8266) ti ulehčí tvůj projekt meteostanice.  
Obsahuje totiž vše, co budeš pro začátek potřebovat — a velmi snadno ji rozšíříš o další moduly s čidly.

---

## 🧩 Specifikace

| Parametr | Hodnota |
|-----------|----------|
| **Verze desky** | v4.1 |
| **Mikrokontrolér** | ESP32-C3-MINI (Wi-Fi, BLE, RISC-V jádro) |
| **Vstupní napětí USB** | 3.4–5.5 V |
| **Vstupní napětí Solar** | 5–10 V *(doporučený 6 V solární panel)* |
| **Odběr proudu v deep-sleep módu** | 23 μA |
| **Konektor pro anténu (IPEX verze)** | [IPEX3](https://www.laskakit.cz/vyhledavani/?string=IPEX3&lb.f%5B%5D=category%3AP%C5%99enos%20a%20ukl%C3%A1d%C3%A1n%C3%AD%20dat&lb.f%5B%5D=category%3APropojovac%C3%AD%20kabely) |
| **Napájení** | USB-C nebo Li-Ion akumulátor (1 článek) |
| **Nabíjecí čip** | BQ24074RGTR s indikací nabíjení *(LED CHG/DONE)* |
| **USB převodník** | CH9102F |
| **Stabilizátory napětí** | RT9080 (ESP), RT9080 (periferie, IO4 → HIGH pro zapnutí) |
| **Rozměry** | 48,4 × 32,9 × 9 mm |
| **Hmotnost** | 8 g |

---

## ⚙️ Pinout desky

Na přední straně desky najdeš Wi-Fi modul s ESP32-C3.  
Ten disponuje vyšším výkonem než starší verze s ESP8266 a také je mnohem úspornější — vlastní spotřeba pouhých **23 μA** v deep-sleep módu.

Tento modul podporuje standard **IEEE 802.11 b/g/n**.  
Na desce jsou dvě tlačítka pro nahrávání kódu — **FLASH** a **RESET**.  
Pájecí můstek **CH_CURRENT** umožňuje volit maximální nabíjecí proud do akumulátoru: **1,0 A nebo 1,34 A** dle osazení rezistoru (viz schéma).

Desku lze vypnout pomocí vypínače na levé straně.  
Na pravé straně se nachází **USB-C konektor** pro napájení a nabíjení akumulátoru.  
Na spodní straně najdeš konektor pro **Li-Ion akumulátor (Battery)** a **solární panel (Solar)**.

Na pravé straně je také **1-Wire sběrnice** pro čidlo **DS18B20** (GPIO10).  
Na levé straně se nachází sada **µŠup konektorů** – to je náš vlastní standard kompatibilní se **SparkFun Qwiic** a **Adafruit STEMMA**.  
Kromě klasického **I2C µŠup konektoru** je zde také **µŠup SPI** a **µŠup IO**.

Napájení µŠup konektorů je řízeno přes **GPIO4 (HIGH = zapnuto)**, což umožňuje ještě nižší spotřebu.  
Regulátor napětí 3.3V je integrován přímo na desce.  
Pro měření napětí akumulátoru je k dispozici odporový dělič (1MΩ a 1,3MΩ) připojený na **IO0 (ADC vstup)**.

![LaskaKit Meteo Mini s ESP32-C3 pinout](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini_ESP32-C3_pin.jpg)  
![LaskaKit Meteo Mini s ESP32-C3 v3.5 a novější pinout](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini-C3_v3.5_pinout.JPG)

---

## 🔌 Připojení senzorů

| Rozhraní | Konektor | Signály |
|-----------|-----------|---------|
| **µŠup I2C** | JST-SH 4 pin | SDA: IO19, SCL: IO18 |
| **µŠup SPI** | JST-SH 6 pin | CS: IO3, MOSI: IO7, SCK: IO6, MISO: IO2 |
| **µŠup IO** | 2× JST-SH 3 pin | IO1, IO10 *(podpora DS18B20)* |

---

## ⚡ Připojení akumulátoru a solárního panelu

Napájení přes USB-C a solární panel je sloučeno přes ochranné diody do vstupu nabíjecího čipu **BQ24074**.  
Souběžné připojení obou zdrojů je tedy bezpečné.  
Doporučený **solární panel je 6 V**, maximálně však lze bezpečně použít i **10V solární panely**.  
Nabíjecí proud je **nastavitelný pomocí pájecích propojek CH_CURRENT** na hodnoty **0.5 A (výchozí)**, **1.0 A**, nebo **1.34 A** *(pokud jsou všechny tři propojky spojeny)*.  
Stav nabíjení je indikován pomocí LED — **CHG** (nabíjení) a **DONE** (nabito).

---

## 🔋 Měření napětí na akumulátoru

Napětí akumulátoru (**VCC**) je přes odporový dělič přivedeno na vstup **IO0** (ADC) mikrokontroléru ESP32-C3.  

---

## 💡 LED a senzory

- **Adresovatelná RGB LED:** SK6812-EC20 na pinu IO9  
- **Tlačítko:** IO5 → stisk = LOW  
- **Teplotní čidlo:** NTC 10 kΩ (3435) – ochrana akumulátoru  

---

## 🧠 Programování

V Arduino IDE nainstalujte [podporu ESP32-C3](https://github.com/espressif/arduino-esp32).  
Pro verze **3.5 a novější** (včetně **v4.1**) již **není potřeba externí programátor** — CH9102F je integrován na desce.  
U starších verzí lze použít [programátor s CH340C](https://www.laskakit.cz/laskakit-ch340-programmer-usb-c--microusb--uart/).

---

## 💾 Vzorový kód

Vzorové kódy a knihovny jsou dostupné na:  
👉 [https://github.com/LaskaKit/Meteo_Mini/tree/main/SW/](https://github.com/LaskaKit/Meteo_Mini/tree/main/SW/)

---

## 📦 K dispozici

Deska je dostupná ve dvou variantách:  
- s **integrovanou PCB anténou**  
- nebo s **konektorem pro externí anténu (IPEX3)**  

👉 [https://www.laskakit.cz/laskakit-meteo-mini/](https://www.laskakit.cz/laskakit-meteo-mini/)

---

## 🧱 Krabička a 3D tisk

K dispozici je i model pro 3D tisk krabičky:

![LaskaKit Meteo Mini 3D case](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini_3Dcase.jpg)

A ano — **to, co prodáváme, sami používáme** (na fotce předchozí verze):

![LaskaKit Meteo Mini Weather Station](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini_weatherstation.jpg)