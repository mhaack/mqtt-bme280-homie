/*
 * BME280Node.h
 * Homie Node for BME280 sensors using Adafruit BME280 library.
 *
 * Version: 1.0
 * Author: Markus Haack (http://github.com/mhaack)
 */

#ifndef SRC_BME280NODE_H_
#define SRC_BME280NODE_H_

#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <SPI.h>
#include <Wire.h>

#include <HomieNode.hpp>

class BME280Node : public HomieNode {
  private:
    unsigned long lastMeasurement;

    Adafruit_BME280 bme;

  public:
    BME280Node(const char *name);

    float getHumidity() const { return humidity; }
    float getTemperature() const { return temperature; }
    float getPressure() const { return pressure; }

  protected:
    virtual void setup() override;
    virtual void loop() override;

  private:
    float temperature = NAN;
    float humidity = NAN;
    float pressure = NAN;
};

#endif
