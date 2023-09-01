#ifndef WING_TRIPLE_SWITCH_H
#define WING_TRIPLE_SWITCH_H

#include "channel.h"

enum TripleSwitchState {
  kUp,
  kMiddle,
  kDown
};

class TripleSwitch : public Channel {
private:
  TripleSwitchState state_ = kUp;
public:
  TripleSwitch(int pin);
  void Update(long value) override;
  TripleSwitchState State();
};


#endif //WING_TRIPLE_SWITCH_H
