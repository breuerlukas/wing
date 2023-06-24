#ifndef WING_KNOB_H
#define WING_KNOB_H

#include "channel.h"

class Knob : public Channel {
public:
  Knob(int pin);
  int Value();
};

#endif //WING_KNOB_H
