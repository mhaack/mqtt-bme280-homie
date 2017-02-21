/*
* RFTransmitterNode.cpp
*
*  Created on: 07.02.2016
*  Author: Markus Haack
*/

#include "RFTransmitterNode.h"
#include <Homie.hpp>

RFTransmitterNode::RFTransmitterNode(const char *name, RCSwitch &rcSwitch)
    : HomieNode(name, "RFTransmitter"), rcSwitch(rcSwitch) {
  advertise("send").settable();
}

bool RFTransmitterNode::handleInput(const String &property,
                                    const HomieRange &range,
                                    const String &value) {
  long int data = 0;
  int pulseLength = 350;
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
  setProperty("send").send(String(data));
  return true;
}
