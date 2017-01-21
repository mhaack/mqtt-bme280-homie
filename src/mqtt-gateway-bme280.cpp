/*
 * mqtt-gateway-bme280.cpp
 *
 * Version: 1.1
 * Author: Markus Haack (http://github.com/mhaack)
 */

#include <Homie.h>
#include <NTPClient.h>
#include <OLEDDisplayUi.h>
#include <SSD1306.h>
#include <WiFiUdp.h>

#include "BME280Node.h"
#include "DisplayNode.h"
#include "LoggerNode.h"
#include "images.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

BME280Node bme280Node;
SSD1306Wire display(0x3c, D2, D1);
OLEDDisplayUi ui(&display);
DisplayNode displayNode(display, ui, timeClient);

// declaring method prototypes
void drawTempFrame(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x,
                   int16_t y);
void drawHumidityFrame(OLEDDisplay *display, OLEDDisplayUiState *state,
                       int16_t x, int16_t y);
void drawPressureFrame(OLEDDisplay *display, OLEDDisplayUiState *state,
                       int16_t x, int16_t y);
void drawMQTTFrame(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x,
                   int16_t y);

void loopHandler() { timeClient.update(); }

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;

  Homie_setFirmware("mqtt-gateway-outdoor", "1.0.0");
  Homie.disableResetTrigger();
  // Homie.disableLedFeedback();
  Homie.setLoggingPrinter(&Serial);
  Homie.setLoopFunction(loopHandler);
  Homie.onEvent([](HomieEvent event) { displayNode.Event(event); });

  LN.setLoglevel(LoggerNode::DEBUG);
  displayNode.addFrame(drawTempFrame, 0);
  displayNode.addFrame(drawHumidityFrame, 1);
  displayNode.addFrame(drawPressureFrame, 2);
  displayNode.addFrame(drawMQTTFrame, 3);
  displayNode.setFrameCount(4);
  displayNode.enableStatusFrame(true);

  Homie.setup();

  timeClient.begin();
}

void drawTempFrame(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x,
                   int16_t y) {
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(x + 64, y + 0, "Temperature");
  display->setFont(ArialMT_Plain_16);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(x + 0, y + 31,
                      String(bme280Node.getTemperature(), 1) + "°C");
}

void drawHumidityFrame(OLEDDisplay *display, OLEDDisplayUiState *state,
                       int16_t x, int16_t y) {
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(x + 64, y + 0, "Humidity");
  display->setFont(ArialMT_Plain_16);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(x + 0, y + 31, String(bme280Node.getHumidity(), 0) + "%");
}

void drawPressureFrame(OLEDDisplay *display, OLEDDisplayUiState *state,
                       int16_t x, int16_t y) {
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(x + 64, y + 0, "Pressure");
  display->setFont(ArialMT_Plain_16);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(x + 0, y + 31,
                      String(bme280Node.getPressure(), 0) + "hPa");
}

void drawMQTTFrame(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x,
                   int16_t y) {
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(x + 64, y + 0, "MQTT");
}

void loop() { Homie.loop(); }
