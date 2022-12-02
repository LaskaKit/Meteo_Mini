# LaskaKit Meteo Mini s ESP32-C3. Výkonnější a úspornější. 
Meteostanice je jeden z projektů, které bastlíři nejčastěji vyhledávají.</br>
Když si blikáš LEDkou, je to sice pěkné, ale za chvíli tě to asi omrzí. Když si postavíš meteostanici, bude ti sloužit dlouho, vlastně čím délé, tím lépe, protože budeš mít dlouhodobé statistiky. A třeba díky vlastní meteostanici dokážeš zachytit výbuch sopky na druhé straně zeměkoule (díky čidlu tlaku, které zaznamená tlakovou vlnu).</br>
Víme, že každý si nedokáže nebo nechce navrhnout vlastní hardware a tak přicházíme s naší vývojovou deskou určenou (nejen) pro meteostanice - [LaskaKit Meteo Mini](https://www.laskakit.cz/laskakit-meteo-mini
).

![LaskaKit Meteo Mini](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/1.jpg)

Tato vývojová deska s ESP32-C3 (což je výrazná změna oproti starší verzi méně úsporné verzi s ESP12S-ESP8266) ti ulehčí tvůj projekt meteostanice. Obsahuje totiž vše, co budeš pro začátek potřebovat. A velmi snad jí rozšíříš o spoustu dalších modulů s čidly. 

## Pinout desky

Na přední straně desky najdeš Wi-Fi modul s ESP32-C3. Ten disponuje vyšším výkonem než starší verze desky s ESP8266 a také je mnohem úspornější - vlastní spotřeba pouhých 5 uA naproti tomu 20 uA, který má ESP8266.</br>
Tento modul podporuje standard IEEE 802.11 b/g/n. Dále na desce najdeš dvě tlačítka pro nahrávání kódu - FLASH a RESET. Postup pro programování bude vysvětlen níže.
Dále zde najdeš i pájecí most nazvaný CH_CURRENT - propájením tohoto mostu vybereš maximální nabíjecí proud do akumulátoru - 260mA a 400mA (výchozí).
Celou desku můžeš vypnout díky vypínači na levé straně. Na pravé straně se pak nachází USB-C konektor (žádný microUSB :) ) určený pro nabíjení akumulátoru. Na spodní straně je konektor pro připojení Li-ion akumulátoru (Battery) a druhý konektor pro připojení solárního panelu (solar). </br>
Na pravé straně ještě najdeš 1-wire sběrnici, kam můžeš zapájet teplotní čidlo DS18B20. Na levé straně desky se nachází μŠup - což je náš standardní typ konektoru, kompatibilní s SparkFun Qwiic a Adafruit STEMMA. </br>
S tímto konektorem máme i vlastní moduly - [SHT40 (teplota/vlhkost)](https://www.laskakit.cz/laskakit-sht40-senzor-teploty-a-vlhkosti-vzduchu/) nebo [SCD41 (teplota/vlhkost/CO2)](https://www.laskakit.cz/laskakit-scd41-senzor-co2--teploty-a-vlhkosti-vzduchu/).</br>

Regulátor na 3.3V se nachází přímo na desce Meteo Mini. </br>
Pro měření akumulátoru můžeš využít odporový dělič napětí, jeho výstup je připojen na IO0. Hodnoty rezistorů jsou 1M a 1,3M. </br>
K I2C sběrnici můžeš připojit i pull-up rezistory, jen dej pozor abys jich neměl na I2C sběrnici připojeno několik. Paralelním spojením rezistorů se snižuje jejich hodnota. Minimální hodnota pull-up rezistorů by měla být 2,2k.</br>
Na spodní části pak najdete programovací konektor.

Spotřeba Meteo Mini s ESP32-C3 je opravdu nízká. V případě napájení z akumulátoru, je spotřeba desky v deep-sleep mode pouze 8 uA. Což je 4x méně než u předchozí verze. 

![LaskaKit Meteo Mini with ESP32-C3 pinout](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMiniPinout.JPG)

## Programování

V Arduino IDE nainstalujte [podporu ESP32-C3](https://github.com/espressif/arduino-esp32).

Pro naprogramování Meteo Mini stačí použít [náš programátor s CH340C](https://www.laskakit.cz/laskakit-ch340-programmer-usb-c--microusb--uart/). Jen jej zastrčíš do konektoru na MeteoMini, přepneš na programátoru napájení na 3.3V a připojíš USB-C nebo microUSB do konektoru počítače. Napíšeš kód a nahraješ.

## Připojení akumulátoru a solárního panelu

Solární panel a USB-C konektor jsou připojeny přes ochranné diody do vstupu nabíjecího obvodu TP4054.</br>
Souběžné připojení microUSB konektoru a solárního panelu je tedy chráněno pomocí diod D1 a D2. </br>
Tento obvod dokáže nabíjet akumulátor proudem až 400 mA (výchozí nastavení pomocí pájecího mostu CH_CURRENT) nebo 280 mA - zde je potřeba přeříznout cestu v pájecím mostu a propájet jeho druhou část.</br>
Maximální vstupní napětí je 9V. Solární panel tedy volte s rezervou pro případ, kdy bude akumulátor plně nabitý a na solární panel bude svítit slunce. V takovém případě může napětí na výstupu solárního panelu dosáhnout vyššího napětí.</br>
Doporučujeme tedy 6V solární panel. 

## Měření napětí na akumulátoru
VCC (napětí akumulátoru) je přes odporový dělič přivedeno na vstup IO0 AD převodníku ESP32-C3. </br>
Maximální vstupní napětí AD převodníku může být 3.3V.

## Vzorový kód
Vytvořili jsme i vzorový kód. Ten najdeš na https://github.com/LaskaKit/Meteo_Mini/tree/main/SW/

K dispozici je osazená deska ve dvou verzích - PCB anténou nebo konektorem pro externí anténu, kterou můžeš zakoupit na laskakit.cz
[https://www.laskakit.cz/laskakit-meteo-mini](https://www.laskakit.cz/laskakit-meteo-mini/)

K dispozici je i soubor pro tisk krabičky na 3D tiskárně...

![LaskaKit Meteo Mini 3D case](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini_3Dcase.jpg)

... a to, co prodáváme, opravdu sami používáme (předchozí verze).

![LaskaKit Meteo Mini Weather Station](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini_weatherstation.jpg)
