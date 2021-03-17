# LaskaKit Meteo Mini
Meteostanice je jeden z projektů, které bastlíři nejčastěji vyhledávají.
Když si blikáte LEDkou, je to sice pěkné, ale za chvíli vás to omrzí. Když si postavíte meteostanici, bude vám sloužit dlouho, vlastně čím délé, tím lépe, protože budete mít dlouhodobé statistiky.
Víme, že každý si nedokáže či nechce navrhnout vlastní hardware a tak přicházíme s naší vývojovou deskou určenou (nejen) pro meteostanice - [LaskaKit Meteo Mini](https://www.laskarduino.cz/laskakit-meteo-mini
).

![LaskaKit Meteo Mini](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini.jpg)

Tato vývojová deska s ESP8266 by vám měla pomoci ve vašem projektu meteostanice. Obsahuje totiž vše, co budete pro začátek potřebovat. 
A pokud bude něco chybět? Není problém desku rozšířit o další moduly skrze přítomné konektory, které jsou pinově kompatibilní s Wemos D1 Mini. 

## Pinout desky

![LaskaKit Meteo Mini TOP](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_pinout_top.jpg)

Na přední straně desky najdete Wi-Fi modul ESP-12S s ESP8266. 
Tento modul podporuje standard IEEE 802.11 b/g/n a také už zmíněné konektory pro rozšiřující desky kompatibilní s pinoutem Wemos D1 Mini. Dále najdete dvě tlačítka pro nahrávání kódu - FLASH a RESET. Postup pro programování bude vysvětlen níže.
Dále zde najdete i pájecí most nazvaný SLEEP (WAKE-UP) - propájením tohoto mostu propojíte RESET pin s GPIO16 (výstup časovače) a jste schopni se probudit z nejhlubšího spánku mikrokontroléru.
Celou desku můžete vypnout díky vypínači na levé straně. Na pravé straně se pak nachází microUSB konektor určený pro nabíjení akumulátoru. Na spodní straně je konektor pro připojení Li-ion akumulátoru (Battery) a druhý konektor pro připojení solárního panelu (solar). 
Na pravé straně ještě najdete 1-wire sběrnici, kam můžete zapájet teplotní čidlo DS18B20.

![LaskaKit Meteo Mini BOTTOM](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_pinout_bottom.jpg)

Na druhé najdete 4pinový konektor s I2C sběrnicí s napájecím napětím 3.3V. Regulátor na 3.3V se nachází přímo na desce Meteo Mini. 
Pro měření akumulátoru můžete využít odporový dělič napětí, jeho připojení provedete propájením ADC pájecího mostu. 
K I2C sběrnici můžete osadit i pull-up rezistory. 
Na spodní části pak najdete programovací konektor, který obsahuje UART sběrnici (RX, TX) a napájení (+5V, GND).

Díky kompatibilitě s Wemos D1 Mini může využít i stejné rozšiřující moduly - [microSD karta](https://www.laskarduino.cz/wemos-d1-mini-microsd-shield/), čidlo teploty a vlhkost [DHT11](https://www.laskarduino.cz/wemos-d1-mini-dht11-shield/)/[DHT22](https://www.laskarduino.cz/wemos-d1-mini-dht22-shield/), [SHT30](https://www.laskarduino.cz/wemos-d1-mini-sht30-shield--i2c/), [BMP180](https://www.laskarduino.cz/wemos-d1-mini-bmp180-shield/) nebo [OLED](https://www.laskarduino.cz/wemos-d1-mini-64x48-oled-displej-shield--i2c/).

Všechny moduly najdete na [https://www.laskarduino.cz/esp-a-wemos/](https://www.laskarduino.cz/esp-a-wemos/)

![LaskaKit Meteo Mini Wemos](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_pinout_wemos.jpg)

## Programování

V Arduino IDE nainstalujte podporu ESP8266

![LaskaKit Meteo Mini Arduino IDE](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_Generic_ESP8266_Module.png)
https://arduino.esp8266.com/stable/package_esp8266com_index.json

![LaskaKit Meteo Mini Arduino IDE Preference](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_Preference.jpg)

Pro naprogramování Meteo Mini je třeba přepnout do boot režimu. To provedete kombinací tlačítek RESET a FLASH. 
Stiskněte tlačítko "FLASH" a držte
Stiskněte tlačítko "RESET", stále držte "FLASH"
Uvolněte tlačítko "RESET" a poté i "FLASH"
Klikněte na tlačítko "Nahrát" v Arduino IDE
Po nahrání kódu stiskněte tlačítko RESET a uvolněte, kód se spustí

![LaskaKit Meteo Mini Programming](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini.gif)

Po přepnutí do boot režimu pak můžete nahrát kód z Arduino IDE. Po nahrání pak Meteo Mini resetujte tlačítkem RESET. Váš program naběhne.

## Připojení akumulátoru a solárního panelu

![LaskaKit Meteo Mini Solar and MicroUSB](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_Solar.jpg)

Solární panel a microUSB konektor jsou připojeny přes ochranné diody do vstupu nabíjecího obvodu TP4054.
Souběžné připojení microUSB konektoru a solárního panelu je tedy chráněno pomocí diod D1 a D2. 
Tento obvod dokáže nabíjet akumulátor proudem až 800 mA.
Maximální vstupní napětí je 9V. Solární panel tedy volte s rezervou pro případ, kdy bude akumulátor plně nabitý a na solární panel bude svítit slunce. V takovém případě může napětí na výstupu solárního panelu dosáhnout vyššího napětí.
Doporučujeme tedy 6V solární panel. 
Nabíjecí proud je definován odporem R11 (aka Rprog) dle vzorce 

![LaskaKit Meteo Mini ADC formula](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_ADC_formula.jpg)

## Měření napětí na akumulátoru
VCC (napětí akumulátoru) je přes odporový dělič přivedeno na vstup AD převodníku ESP8266. 
Maximální vstupní napětí AD převodníku může být 1V.

![LaskaKit Meteo Mini ADC](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/LaskaKit_MeteoMini_ADC.jpg)

## Vzorový kód
Vytvořili jsme i vzorový kód. Ten najdete na https://github.com/LaskaKit/Weather_Station_Mini

Meteo Mini čte z čidel teplotu, tlak a vlhkost a posílá je do služby Thingspeak.

K dispozici je osazená deska bez I2C konektoru, kterou můžete zakoupit na laskarduino.cz
https://www.laskarduino.cz/laskakit-meteo-mini

K dispozici je i soubor pro tisk krabičky na 3D tiskárně...

![LaskaKit Meteo Mini 3D case](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini_3Dcase.jpg)

... a to, co prodáváme, opravdu sami používáme.

![LaskaKit Meteo Mini Weather Station](https://github.com/LaskaKit/Meteo_Mini/blob/main/img/MeteoMini_weatherstation.jpg)
