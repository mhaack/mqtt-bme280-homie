/*
 * mqtt-gateway-bme280.cpp
 *
 * Version: 1.0.0
 * Author: Markus Haack (http://github.com/mhaack)
 */

#include <Homie.h>
#include <NTPClient.h>
#include <OLEDDisplayUi.h>
#include <SSD1306.h>
#include <WiFiUdp.h>

#include "BME280Node.h"
#include "DisplayNode.h"
#include "RFReceiverNode.h"
#include "RFTransmitterNode.h"
#include "images.h"

// init time client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

// init rc library
RCSwitch mySwitch = RCSwitch();

// init Homie nodes
BME280Node bme280Node("bme280Outdoor");
RFReceiverNode rfReceiverNode("rfRxOutdoor", mySwitch);
RFTransmitterNode rfTransmitterNode("rfTxOutdoor", mySwitch);

// init display & display node
SSD1306Wire display(0x3c, D2, D1);
OLEDDisplayUi ui(&display);
DisplayNode displayNode("displayOutdoor", display, ui, timeClient);

// declaring method prototypes
void drawTempFrame(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x,
                   int16_t y);
void drawHumidityFrame(OLEDDisplay *display, OLEDDisplayUiState *state,
                       int16_t x, int16_t y);
void drawPressureFrame(OLEDDisplay *display, OLEDDisplayUiState *state,
                       int16_t x, int16_t y);
void drawRFTransmitFrame(OLEDDisplay *display, OLEDDisplayUiState *state,
                         int16_t x, int16_t y);

void loopHandler() { timeClient.update(); }

void setup() {
  Serial.begin(115200);
  Serial << endl << endl;

  // init RF library
  mySwitch.enableTransmit(15);    // RF Transmitter on pin D8
  mySwitch.setRepeatTransmit(20); // increase transmit repeat
  mySwitch.enableReceive(13);     // RF Receiver on pin D7

  Homie_setFirmware("mqtt-gateway-outdoor", "1.0.0");
  Homie.disableResetTrigger();
  // Homie.disableLedFeedback();
  Homie.setLoggingPrinter(&Serial);
  Homie.setLoopFunction(loopHandler);
  Homie.onEvent([](HomieEvent event) { displayNode.Event(event); });

  displayNode.addFrame(drawTempFrame, 0);
  displayNode.addFrame(drawHumidityFrame, 1);
  displayNode.addFrame(drawPressureFrame, 2);
  displayNode.addFrame(drawRFTransmitFrame, 3);
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
  display->drawXbm(x + 5, y + 18, temp_icon_width, temp_icon_height,
                   temp_icon_bits);
  display->setFont(ArialMT_Plain_24);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(x + 42, y + 20,
                      String(bme280Node.getTemperature(), 1) + " °C");
}

void drawHumidityFrame(OLEDDisplay *display, OLEDDisplayUiState *state,
                       int16_t x, int16_t y) {
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(x + 64, y + 0, "Humidity");
  display->drawXbm(x + 5, y + 18, humidity_width, humidity_height,
                   humidity_bits);
  display->setFont(ArialMT_Plain_24);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(x + 55, y + 20,
                      String(bme280Node.getHumidity(), 0) + " %");
}

void drawPressureFrame(OLEDDisplay *display, OLEDDisplayUiState *state,
                       int16_t x, int16_t y) {
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(x + 64, y + 0, "Pressure");
  display->drawXbm(x + 5, y + 18, pressure_width, pressure_height,
                   pressure_bits);
  display->setFont(ArialMT_Plain_16);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(x + 50, y + 25,
                      String(bme280Node.getPressure(), 0) + " hPa");
}

void drawRFTransmitFrame(OLEDDisplay *display, OLEDDisplayUiState *state,
                         int16_t x, int16_t y) {
  display->setFont(ArialMT_Plain_10);
  display->setTextAlignment(TEXT_ALIGN_CENTER);
  display->drawString(x + 64, y + 0, "RF Transmit");
  display->drawXbm(x + 5, y + 18, arrows_width, arrows_height, arrows_bits);
  display->setFont(ArialMT_Plain_16);
  display->setTextAlignment(TEXT_ALIGN_LEFT);
  display->drawString(x + 50, y + 25, rfTransmitterNode.getLastEvent());
}

void loop() { Homie.loop(); }
