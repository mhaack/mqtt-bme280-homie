/*
* DisplayNode.cpp
* Homie Node for SSD1306 OLED displays using ESP8266_SSD1306 display driver
* library.
*
* Version: 1.0
* Author: Markus Haack (http://github.com/mhaack)
*/

#include "DisplayNode.h"
#include "images.h"

#include <ESP8266WiFi.h>
#include <Homie.hpp>

HomieEvent homieEvent;

DisplayNode::DisplayNode(SSD1306Wire &display, OLEDDisplayUi &ui,
                         NTPClient &timeClient)
    : HomieNode("OLEDDisplay", "display"), display(display), ui(ui),
      timeClient(timeClient), statusEnabled(false) {}

void DisplayNode::setup() {

  // init dispaly
  ui.setTargetFPS(60);
  ui.setActiveSymbol(emptySymbol);
  ui.setInactiveSymbol(emptySymbol);
  ui.disableIndicator();
  ui.setIndicatorPosition(BOTTOM);

  ui.getUiState()->userData = this;

  ui.setIndicatorDirection(LEFT_RIGHT);
  ui.setFrameAnimation(SLIDE_LEFT);

  // Add frames
  if (statusEnabled) {
    addFrame(DisplayNode::drawStatusFrame, frameCount);
    frameCount++;
  }
  ui.setFrames(frames, frameCount);

  // Add overlays
  static OverlayCallback overlays[] = {DisplayNode::drawOverlay};
  static uint8_t overlaysCount = 1;
  ui.setOverlays(overlays, overlaysCount);

  // Initialising the UI will init the display too.
  ui.init();

  display.flipScreenVertically();

  Homie.getLogger() << "OLED DisplayNode setup successfull!" << endl;
}

void DisplayNode::loop() { ui.update(); }

void DisplayNode::addFrame(FrameCallback frame, uint8_t index) {
  frames[index] = frame;
}

void DisplayNode::Event(HomieEvent event) { homieEvent = event; }

void DisplayNode::drawStatusFrame(OLEDDisplay *display,
                                  OLEDDisplayUiState *state, int16_t x,
                                  int16_t y) {
  if ((state == NULL) || (state->userData == NULL)) {
    return;
  }
  const DisplayNode *self = static_cast<DisplayNode *>(state->userData);

  if (self != NULL) {
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_10);
    display->drawString(64 + x, 0 + y, "System Status");

    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->drawString(0 + x, 13 + y, "IP: " + homieEvent.ip.toString());

    String last_status = "unknown";
    switch (homieEvent.type) {
    case HomieEventType::CONFIGURATION_MODE:
      last_status = "Configuration mode started";
      break;
    case HomieEventType::NORMAL_MODE:
      last_status = "Normal mode started";
      break;
    case HomieEventType::OTA_STARTED:
      last_status = "OTA started";
      break;
    case HomieEventType::OTA_FAILED:
      last_status = "OTA failed";
      break;
    case HomieEventType::OTA_SUCCESSFUL:
      last_status = "OTA successful";
      break;
    case HomieEventType::ABOUT_TO_RESET:
      last_status = "About to reset";
      break;
    case HomieEventType::WIFI_CONNECTED:
      last_status = "Wi-Fi connected";
      break;
    case HomieEventType::WIFI_DISCONNECTED:
      last_status = "Wi-Fi disconnected";
      break;
    case HomieEventType::MQTT_CONNECTED:
      last_status = "MQTT connected";
      break;
    case HomieEventType::MQTT_DISCONNECTED:
      last_status = "MQTT disconnected";
      break;
    case HomieEventType::MQTT_PACKET_ACKNOWLEDGED:
      last_status = "MQTT package acknowledged";
      break;
    }
    display->drawStringMaxWidth(0 + x, 24 + y, 128, "Status: " + last_status);
  }
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

void DisplayNode::drawOverlay(OLEDDisplay *display, OLEDDisplayUiState *state) {
  if ((state == NULL) || (state->userData == NULL)) {
    return;
  }
  const DisplayNode *self = static_cast<DisplayNode *>(state->userData);

  if (self != NULL) {
    display->setColor(WHITE);
    display->setFont(ArialMT_Plain_10);
    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->drawString(0, 54,
                        String(state->currentFrame + 1) + "/" +
                            String(self->frameCount));

    String time = self->timeClient.getFormattedTime();
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->drawString(64, 54, time);

    int8_t wifiQuality = getWifiQuality();
    for (int8_t i = 0; i < 4; i++) {
      for (int8_t j = 0; j < 2 * (i + 1); j++) {
        if ((wifiQuality > i * 25) || (j == 0)) {
          display->setPixel(120 + 2 * i, 63 - j);
        }
      }
    }
    display->drawHorizontalLine(0, 13, 128);
    display->drawHorizontalLine(0, 52, 128);
  }
}
