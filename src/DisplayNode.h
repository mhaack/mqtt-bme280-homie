/*
* DisplayNode.h
* Homie Node for SSD1306 OLED displays using ESP8266_SSD1306 display driver
* library.
*
* Version: 1.0
* Author: Markus Haack (http://github.com/mhaack)
*/

#ifndef SRC_DISPLAYNODE_H_
#define SRC_DISPLAYNODE_H_

#include <HomieNode.hpp>
#include <NTPClient.h>
#include <OLEDDisplayUi.h>
#include <SSD1306.h>

class DisplayNode : public HomieNode {
    static const int MAXFRAMES = 7;

  public:
    DisplayNode(const char *name, SSD1306Wire &display, OLEDDisplayUi &ui, NTPClient &timeClient);

    int addFrame(FrameCallback frame);
    void enableStatusFrame(bool enabled) { statusEnabled = enabled; }
    void Event(HomieEvent event);

  protected:
    virtual void setup() override;
    virtual void loop() override;

  private:
    SSD1306Wire display;
    OLEDDisplayUi ui;
    NTPClient &timeClient;
    FrameCallback frames[MAXFRAMES];
    OverlayCallback overlays[1];
    int frameCount = 0;
    bool statusEnabled;

    static void drawOverlay(OLEDDisplay *display, OLEDDisplayUiState *state);
    static void drawStatusFrame(OLEDDisplay *display, OLEDDisplayUiState *state, int16_t x, int16_t y);
};

#endif
