### Version 4.0
- Made it smaller
- Redo power line, LDO chnaged to RT9080
- Wemos pins deleted
- added Neopixel LED
- added µŠup SPI connector+
- added 2x µŠup IO connectors (one with optional pull-up for DS18B20)
#### Version 3.6
- přidán kondenzátor C8 na vstup spínače AP2191
#### Version 3.5
* nevypíná se spínaný stabilizátor pokud není na výstup připojena zátěž a deska v deepsleepu bere cca 200uA.
problém odstraněn přidáním kondenzátoru C8 na vstup spínače AP2191
- změna modulu ESP na ESP32-C3-MINI
- integrován programátor
- přidán spínaný stabilizátor pro napájení periferií - AP2191WG + ME6211C33M5G (pin IO03)
#### Version 3.2
- i2C pins were swapped to mit Wemos D1 mini shields spec. | Piny i2C byly prohozený aby odpovídali shieldům pro Wemos D1.
- ADC jumper now is closed by default | Propojka ADC je nyní ve výchozím nastavení uzavřena
#### Version 3.1
Adjusted resistor values in the resistance divider to 1M/1.3M, ADC max. input voltage stays the same. | Upraveny hodnoty rezistorů v odporovém děliči na 1M/1.3M, ADC max. vstupní napětí zůstává stejné.
#### Version 3.0
Change ESP12 to ESP32-C3| Změna ESP12 na ESP32-C3
#### Version 2.2
- Voltager devider GPIIO0 (Bat_ADC) changed to 100k/130k ADC max. input voltage is 4.423 V | Dělič napětí GPIIO0 (Bat_ADC) změněn na 100k/130k ADC max. vstupní napětí je 4,423 V
- Voltager devider GPIIO1 (Solar_ADC) changed to 1M/330k ADC max. input voltage is 10.076 V | Dělič napětí GPIIO1 (Solar_ADC) změněn na 1M/330k ADC max. vstupní napětí je 10.076 V
#### Version 2.1
- Initial | Počáteční
