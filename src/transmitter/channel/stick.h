#ifndef PLANE_STICK_H
#define PLANE_STICK_H

#include "channel.h"

class Stick : public Channel {
public:
  Stick(int id);
  int Value();
};


#endif //PLANE_STICK_H
