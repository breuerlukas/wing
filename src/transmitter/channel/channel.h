#ifndef PLANE_CHANNEL_H
#define PLANE_CHANNEL_H

#include "Arduino.h"

class Channel {
private:
  int pin_;
protected:
  long value;
public:
  Channel(int pin);
  void Initialize();
  virtual void Update(long value);
  int Pin();
protected:
  long Read();
};


#endif //PLANE_CHANNEL_H
