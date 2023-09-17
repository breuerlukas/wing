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
  boolean is_state_changing_ = false;
  TripleSwitchState FindState(long value);
public:
  TripleSwitch(int pin);
  void Update(long value) override;
  TripleSwitchState State();
};


#endif //WING_TRIPLE_SWITCH_H
