/*
 * RFTransmitterNode.h
 *
 *  Created on: 07.02.2016
 *  Author: Markus Haack
 */

#ifndef SRC_RFTRANSMITTERNODE_H_
#define SRC_RFTRANSMITTERNODE_H_

#include <HomieNode.hpp>
#include <RCSwitch.h>

class RFTransmitterNode : public HomieNode {

public:
  RFTransmitterNode(const char *name, RCSwitch &rcSwitch);
  String getLastEvent();
  
protected:
  virtual bool handleInput(const String &property, const HomieRange &range,
                           const String &value) override;

private:
  RCSwitch &rcSwitch;
};

#endif /* SRC_RFTRANSMITTERNODE_H_ */
