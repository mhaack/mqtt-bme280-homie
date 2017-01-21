/*
 * mqtt-gateway-bme280.cpp
 *
 * Version: 1.1
 * Author: Markus Haack (http://github.com/mhaack)
 */

#include <Homie.h>
#include <SSD1306.h>
#include <OLEDDisplayUi.h>

#include "LoggerNode.h"
#include "BME280Node.h"
#include "DisplayNode.h"
#include "images.h"

BME280Node bme280Node;
SSD1306Wire display(0x3c, D2, D1);
OLEDDisplayUi ui(&display);
DisplayNode displayNode(display, ui);

//declaring method prototypes
static int8_t getWifiQuality();
void drawTempFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void drawHumidityFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void drawPressureFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);
void drawMQTTFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y);

void loopHandler() {
  displayNode.setWifiQuality(getWifiQuality());
}

void setup() {
    Serial.begin(115200);
    Serial << endl << endl;

    Homie_setFirmware("mqtt-gateway-outdoor", "1.0.0");
    Homie.disableResetTrigger();
    // Homie.disableLedFeedback();
    Homie.setLoggingPrinter(&Serial);
    Homie.setLoopFunction(loopHandler);
    Homie.onEvent([](HomieEvent event) {displayNode.Event(event);});

    LN.setLoglevel(LoggerNode::DEBUG);
    displayNode.addFrame(drawTempFrame, 0);
    displayNode.addFrame(drawHumidityFrame, 1);
    displayNode.addFrame(drawPressureFrame, 2);
    displayNode.addFrame(drawMQTTFrame, 3);
    displayNode.setFrameCount(4);
    displayNode.enableStatusFrame(true);

    Homie.setup();
}

void drawTempFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(x + 65, y +31, "Temperature");
}

void drawHumidityFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(x + 65, y +31, "Humidity");
}

void drawPressureFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(x + 65, y +31, "Pressure");
}

void drawMQTTFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  display->setTextAlignment(TEXT_ALIGN_RIGHT);
  display->setFont(ArialMT_Plain_10);
  display->drawString(x + 65, y +31, "MQTT");
}

// converts the dBm to a range between 0 and 100%
static int8_t getWifiQuality() {
    int32_t dbm = WiFi.RSSI();

    if (dbm <= -100) {
        return 0;
    } else if (dbm >= -50) {
        return 100;
    } else {
        return 2 * (dbm + 100);
    }
}

void loop() {
    Homie.loop();
}
