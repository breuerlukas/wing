#ifndef PLANE_STICK_H
#define PLANE_STICK_H

#include "channel.h"

class Stick : public Channel {
private:
  int value_;
public:
  Stick(int pin);
  void Update(long value) override;
  int Value();
};


#endif //PLANE_STICK_H
