/*
 * RFReceiverNode.h
 *
 *  Created on: 07.02.2016
 *  Author: Markus Haack
 */

#ifndef SRC_RFRECEIVERNODE_H_
#define SRC_RFRECEIVERNODE_H_

#include <HomieNode.hpp>
#include <RCSwitch.h>

class RFReceiverNode : public HomieNode {

public:
  RFReceiverNode(const char *name);

protected:
  virtual void setup() override;
  virtual void loop() override;

private:
  String getChannelByCode(const String &currentCode);
  RCSwitch mySwitch;
};

#endif /* SRC_RFRECEIVERNODE_H_ */
