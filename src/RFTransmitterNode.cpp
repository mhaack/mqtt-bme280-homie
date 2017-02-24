/*
* RFTransmitterNode.cpp
*
*  Created on: 07.02.2016
*  Author: Markus Haack
*/

#include "RFTransmitterNode.h"
#include <Homie.hpp>

const int DEFAULT_PULSE_LENGTH = 350;
long int data = 0;

RFTransmitterNode::RFTransmitterNode(const char *name, RCSwitch &rcSwitch)
    : HomieNode(name, "RFTransmitter"), rcSwitch(rcSwitch) {
  advertise("data").settable();
}

bool RFTransmitterNode::handleInput(const String &property,
                                    const HomieRange &range,
                                    const String &value) {
  int pulseLength = DEFAULT_PULSE_LENGTH;
  if (value.indexOf(',') > 0) {
    pulseLength = atoi(value.substring(0, value.indexOf(',')).c_str());
    data = atoi(value.substring(value.indexOf(',') + 1).c_str());
  } else {
    data = atoi(value.c_str());
  }
  Homie.getLogger() << "Receiving MQTT > 433Mhz signal: " << pulseLength << ":"
                    << data << endl;

  rcSwitch.setPulseLength(pulseLength);
  rcSwitch.send(data, 24);
  setProperty("data").send(String(data));
  return true;
}

String RFTransmitterNode::getLastEvent() {
  if (data == 0) {
    return "---";
  } else {
    return String(data);
  }
}
