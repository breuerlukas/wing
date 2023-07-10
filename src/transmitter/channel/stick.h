#ifndef WING_STICK_H
#define WING_STICK_H

#include "channel.h"

class Stick : public Channel {
public:
  Stick(int id);
  int Value();
};


#endif //WING_STICK_H
