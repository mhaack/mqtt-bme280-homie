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

BME280Node::BME280Node(const char *name) : HomieNode(name, "BME280Sensor"), _lastMeasurement(0) {}

void BME280Node::setup() {
    advertise("temperature");
    advertise("temperature/unit");
    advertise("humidity");
    advertise("humidity/unit");
    advertise("pressure");
    advertise("pressure/unit");

    _measurementInterval = sensorIntervalSetting.get();
    _temperatureOffset = temperatureOffsetSetting.get();

    if (bme.begin()) {
        _sensorFound = true;
        Homie.getLogger() << "BME280 sensor found" << endl
                          << "Reading interval: " << _measurementInterval << " s" << endl
                          << "Temperature offset: " << _temperatureOffset << " °C" << endl;
    } else {
        _sensorFound = false;
        Homie.getLogger() << "BME280 sensor not found. Check wiring!" << endl;
    }
}

void BME280Node::setupHandler() {
    setProperty("temperature/unit").send("°C");
    setProperty("humidity/unit").send("%");
    setProperty("pressure/unit").send("hPa");
};

void BME280Node::loop() {
    if (_sensorFound) {
        if (millis() - _lastMeasurement >= _measurementInterval * 1000UL || _lastMeasurement == 0) {
            temperature = bme.readTemperature();
            humidity = bme.readHumidity();
            pressure = bme.readPressure() / 100.0F;

            Homie.getLogger() << "Temperature: " << temperature << " °C" << endl;
            temperature += temperatureOffsetSetting.get();
            Homie.getLogger() << "Temperature (after offset): " << temperature << " °C" << endl;
            Homie.getLogger() << "Humidity: " << humidity << " %" << endl;
            Homie.getLogger() << "Pressure: " << pressure << " hPa" << endl;

            setProperty("temperature").send(String(temperature));
            setProperty("humidity").send(String(humidity));
            setProperty("pressure").send(String(pressure));

            _lastMeasurement = millis();
        }
    }
}
