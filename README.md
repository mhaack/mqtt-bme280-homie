# Homie Sensor project with BME280  

[![Build Status](https://img.shields.io/travis/mhaack/mqtt-bme280-homie.svg?style=flat-square)](https://travis-ci.org/mhaack/mqtt-bme280-homie)
[![GitHub release](https://img.shields.io/github/release/mhaack/mqtt-bme280-homie.svg?style=flat-square)]
(https://github.com/mhaack/mqtt-bme280-homie/releases)

The mqtt-bme280-homie project is a small and easy to integrate temperature, air pressure and humidity monitoring solution with an extra SSD1306 OLED display. Sensor data is send via MQTT and displayed on the small screen. Local time is loaded via NTP. The project is built with a cost-effective ESP8266 WiFi chip (I used a NodeMCU from ebay, Wemos D1 mini will do as well).

The software is based on [Homie](https://github.com/marvinroger/homie-esp8266) to enable an easy integration with home automation systems like [OpenHab](http://www.openhab.org).

## Hardware

- ESP8266 (Wemos D1 mini, Nodemcu)
- BME280 sensor breakout
- SSD1306 OLED display
- USB power supply and cable
- Enclosure

I got the BME280 breakout form [Adafruit](https://www.adafruit.com/product/2652), others will do as well. The SSD1306 OLED displays I ordered at Aliexpress. This [enclosure](https://www.amazon.de/gp/product/B00PZYMLJ4) keeps everything together.

## Software

The following software libraries are used. If using PlatformIO all dependencies are resolved automatically.

- [Homie V2](https://github.com/marvinroger/homie-esp8266) (dev) including dependencies
- [Adafruit BME280 Driver](https://github.com/adafruit/Adafruit_BME280_Library)
- [Adafruit Unified Sensor](https://github.com/adafruit/Adafruit_Sensor)
- [SSD1306 driver for ESP8266 platform](https://github.com/squix78/esp8266-oled-ssd1306)
- [NTPClient to connect to a time server](https://github.com/arduino-libraries/NTPClient)
- Optionally PlatformIO environment for building the code

## Config

The following config parameters are available via MQTT message (see Homie documentation how to use):

Parameter           | Type        | Usage
------------------- | ----------- | -------
sensorInterval      | long        | temperature reading interval in seconds
temperatureOffset   | double      | temperature offset (-/+) to correct the sensor reading, for example if used in enclosure box
flipScreen          | bool        | filp the display screen vertically
