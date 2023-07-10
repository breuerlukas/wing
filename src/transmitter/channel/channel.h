#ifndef WING_CHANNEL_H
#define WING_CHANNEL_H

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


#endif //WING_CHANNEL_H
