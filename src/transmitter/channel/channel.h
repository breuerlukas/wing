#ifndef PLANE_CHANNEL_H
#define PLANE_CHANNEL_H

#include "Arduino.h"

class Channel {
private:
  int id_;
protected:
  long value;
public:
  Channel(int id);
  virtual void Update(long value);
  int Id();
};


#endif //PLANE_CHANNEL_H
