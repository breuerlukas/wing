#ifndef PLANE_SWITCH_H
#define PLANE_SWITCH_H

#include "channel.h"

enum State {
  kOn,
  kOff
};

class Switch : public Channel {
private:
  State state_;
public:
  Switch(int pin);
  void Update(long value) override;
  State State();
};


#endif //PLANE_SWITCH_H
