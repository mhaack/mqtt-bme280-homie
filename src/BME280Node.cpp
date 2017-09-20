/*
 * BME280Node.cpp
 * Homie Node for BME280 sensors using Adafruit BME280 library.
 *
 * Version: 1.0
 * Author: Markus Haack (http://github.com/mhaack)
 */

#include "BME280Node.h"
#include <Homie.hpp>

HomieSetting<long> sensorIntervalSetting("sensorInterval", "The sensor reading interval in seconds");
HomieSetting<double> temperatureOffsetSetting("temperatureOffset", "The temperature offset in degrees");

BME280Node::BME280Node(const char *name) : HomieNode(name, "BME280Sensor"), lastMeasurement(0) {
    advertise("temperature");
    advertise("humidity");
    advertise("pressure");
}

void BME280Node::setup() {
    if (!bme.begin()) {
        Homie.getLogger() << "Could not find a valid BME280 sensor, check wiring!" << endl;
        while (1)
            ;
    }
    Homie.getLogger() << "BME280 sensor reading interval = " << sensorIntervalSetting.get() << endl;
    Homie.getLogger() << "BME280 temperature offset = " << temperatureOffsetSetting.get() << endl;
    Homie.getLogger() << "BME280 sensor setup successfull!" << endl;
}

void BME280Node::loop() {
    if (millis() - lastMeasurement >= sensorIntervalSetting.get() * 1000UL || lastMeasurement == 0) {
        temperature = bme.readTemperature();
        humidity = bme.readHumidity();
        pressure = bme.readPressure() / 100.0F;

        Homie.getLogger() << "Temperature: " << temperature << " °C" << endl;
        temperature += temperatureOffsetSetting.get();
        Homie.getLogger() << "Temperature (after offset): " << temperature << " °C" << endl;
        Homie.getLogger() << "Humidity: " << temperature << " %" << endl;
        Homie.getLogger() << "Pressure: " << pressure << " hPa" << endl;

        lastMeasurement = millis();

        setProperty("temperature").send(String(temperature));
        setProperty("humidity").send(String(humidity));
        setProperty("pressure").send(String(pressure));
    }
}
