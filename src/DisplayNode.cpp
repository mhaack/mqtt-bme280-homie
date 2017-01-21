/*
* DisplayNode.cpp
* Homie Node for SSD1306 OLED displays using ESP8266_SSD1306 display driver library.
*
* Version: 1.0
* Author: Markus Haack (http://github.com/mhaack)
*/

#include "DisplayNode.h"
#include "LoggerNode.h"
#include "images.h"

#include <ESP8266WiFi.h>
#include <Homie.hpp>

HomieEvent homieEvent;

DisplayNode::DisplayNode(SSD1306Wire& display, OLEDDisplayUi& ui) : HomieNode("OLEDDisplay", "display"),
display(display), ui(ui), statusEnabled(false) {}

void DisplayNode::setup() {
  ui.setTargetFPS(30);

  // Customize the active and inactive symbol
  ui.setActiveSymbol(emptySymbol);
  ui.setInactiveSymbol(emptySymbol);
  ui.disableIndicator();

  ui.getUiState()->userData = this;

  // You can change this to
  // TOP, LEFT, BOTTOM, RIGHT
  ui.setIndicatorPosition(BOTTOM);

  // Defines where the first frame is located in the bar.
  ui.setIndicatorDirection(LEFT_RIGHT);

  // You can change the transition that is used
  // SLIDE_LEFT, SLIDE_RIGHT, SLIDE_UP, SLIDE_DOWN
  ui.setFrameAnimation(SLIDE_LEFT);

  // Add frames
  if (statusEnabled) {
    addFrame(DisplayNode::drawStatusFrame, frameCount);
    frameCount++;
  }
  ui.setFrames(frames, frameCount);

  // Add overlays
  static OverlayCallback overlays[] = { DisplayNode::drawOverlay };
  static int overlaysCount       = 1;
  ui.setOverlays(overlays, overlaysCount);

  // Initialising the UI will init the display too.
  ui.init();

  display.flipScreenVertically();

  LN.log("DisplayNode::setup()", LoggerNode::DEBUG, "OLED DisplayNode setup successfull!");
}

void DisplayNode::loop() {
  ui.update();
}

void DisplayNode::addFrame(FrameCallback frame, uint8_t index) {
  frames[index] = frame;
}

void DisplayNode::Event(HomieEvent event) {
  homieEvent = event;
}

void DisplayNode::drawStatusFrame(OLEDDisplay *display, OLEDDisplayUiState* state, int16_t x, int16_t y) {
  if ((state == NULL) || (state->userData == NULL)) {
    return;
  }
  const DisplayNode *self = static_cast<DisplayNode *>(state->userData);

  if (self != NULL) {
    display->setTextAlignment(TEXT_ALIGN_CENTER);
    display->setFont(ArialMT_Plain_10);
    display->drawString(64 + x, 0 + y, "System Status");

    display->setTextAlignment(TEXT_ALIGN_LEFT);
    display->drawString(0 + x, 10 + y, "IP: " + homieEvent.ip.toString());

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
    display->drawStringMaxWidth(0 + x, 20 + y, 128, "Status: " + last_status);
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

      // String time;
      // self->timeClient.getFormattedTime(time);
      // time = time.substring(0, 5);
      // display->setTextAlignment(TEXT_ALIGN_CENTER);
      // display->drawString(38, 54, time);

      for (int8_t i = 0; i < 4; i++) {
        for (int8_t j = 0; j < 2 * (i + 1); j++) {
          if ((self->wifiQuality > i * 25) || (j == 0)) {
            display->setPixel(120 + 2 * i, 63 - j);
          }
        }
      }

      display->drawHorizontalLine(0, 52, 128);
    }
  }
