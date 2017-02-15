/*
* RFReceiverNode.cpp
*
*  Created on: 07.02.2016
*  Author: Markus Haack
*/

#include "RFReceiverNode.h"
#include <Homie.hpp>

// homie settings
HomieSetting<const char *>
    channelMappingSetting("channels",
                          "Mapping of 433MHz signals to mqtt channels.");

RFReceiverNode::RFReceiverNode(const char *name)
    : HomieNode(name, "RFReceiver") {
  advertise("channel-0");
  mySwitch = RCSwitch();
}

void RFReceiverNode::setup() {
  // init RF library
  mySwitch.enableTransmit(15); // RF Transmitter is connected to Pin D8
  mySwitch.setRepeatTransmit(
      20); // increase transmit repeat to avoid lost of rf sendings
  mySwitch.enableReceive(13); // Receiver on pin D7

  Homie.getLogger() << "RFReceiverNode channel config = "
                    << channelMappingSetting.get() << endl;
  Homie.getLogger() << "RFReceiverNode successfull initialized" << endl;
}

void RFReceiverNode::loop() {
  if (mySwitch.available()) {
    long data = mySwitch.getReceivedValue();
    mySwitch.resetAvailable();
    Homie.getLogger() << "Receiving 433Mhz > MQTT signal: " << data << endl;

    String currentCode = String(data);
    String channelId = getChannelByCode(currentCode);
    Homie.getLogger() << "Code: " << currentCode << " matched to channel "
                      << channelId << endl;
    setProperty("channel-" + channelId).send(currentCode);
  }
}

String RFReceiverNode::getChannelByCode(const String &currentCode) {
  String mappingConfig = channelMappingSetting.get();
  String mapping = "";
  String codes = "";
  int lastIndex = 0;
  int lastCodeIndex = 0;

  for (int i = 0; i < mappingConfig.length(); i++) {
    if (mappingConfig.substring(i, i + 1) == ";") {
      mapping = mappingConfig.substring(lastIndex, i);
      // Serial << "mapping: " << mapping << endl;

      codes = mapping.substring(mapping.indexOf(':') + 2, mapping.length() - 1);
      for (int j = 0; j < codes.length(); j++) {
        if (codes.substring(j, j + 1) == ",") {
          if (currentCode.indexOf(codes.substring(lastCodeIndex, j)) > -1) {
            return mapping.substring(0, mapping.indexOf(':'));
            ;
          }
          codes = codes.substring(j + 1, codes.length());
        }
      }
      if (currentCode.indexOf(codes) > -1) {
        return mapping.substring(0, mapping.indexOf(':'));
        ;
      }
      lastIndex = i + 1;
    }
  }
  return "0";
}
