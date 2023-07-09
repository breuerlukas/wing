#ifndef PLANE_SWITCH_H
#define PLANE_SWITCH_H

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


#endif //PLANE_SWITCH_H
