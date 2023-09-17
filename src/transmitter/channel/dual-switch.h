#ifndef WING_DUAL_SWITCH_H
#define WING_DUAL_SWITCH_H

#include "channel.h"

enum DualSwitchState {
  kOn,
  kOff
};

class DualSwitch : public Channel {
private:
  DualSwitchState state_ = kOff;
  boolean is_state_changing_ = false;
  DualSwitchState FindState(long value);
public:
  DualSwitch(int pin);
  void Update(long value) override;
  DualSwitchState State();
};


#endif //WING_DUAL_SWITCH_H
