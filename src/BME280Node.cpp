/*
 * BME280Node.cpp
 * Homie Node for BME280 sensors using Adafruit BME280 library.
 *
 * Version: 1.0
 * Author: Markus Haack (http://github.com/mhaack)
 */

#include "BME280Node.h"
#include "LoggerNode.h"
#include <Homie.hpp>

BME280Node::BME280Node() :
HomieNode("BME280-Sensor", "bme280"),
lastMeasurement(0) {
    advertise("degrees");
    advertise("rel%");
    advertise("hPa");
}

void BME280Node::setup() {
    if (!bme.begin()) {
        LN.log("BME280Node::setup()", LoggerNode::DEBUG, "Could not find a valid BME280 sensor, check wiring!");
        while (1);
    }
    LN.log("BME280Node::setup()", LoggerNode::DEBUG, "BME280 sensor setup successfull!");
}

void BME280Node::loop() {
    if (millis() - lastMeasurement >= 10000UL || lastMeasurement == 0) {
        temperature = bme.readTemperature();
        humidity = bme.readHumidity();
        pressure = bme.readPressure() / 100.0F;
        lastMeasurement = millis();
        setProperty("degrees").send(String(temperature));
        setProperty("rel%").send(String(humidity));
        setProperty("hPa").send(String(pressure));
    }
}