#ifndef WING_SWITCH_H
#define WING_SWITCH_H

#include "channel.h"

enum SwitchState {
  kOn,
  kOff
};

class Switch : public Channel {
private:
  SwitchState state_ = kOff;
public:
  Switch(int pin);
  void Update(long value) override;
  SwitchState State();
};


#endif //WING_SWITCH_H
