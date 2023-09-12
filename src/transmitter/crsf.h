#ifndef CRSF_h
#define CRSF_h

#include "Arduino.h"

#define CSRF_ADDRESS 0xC8
#define CSRF_LENGTH 0x18
#define CSRF_FRAMEID 0x16

class CRSF {
public:
  CRSF(HardwareSerial& serial);
  void Begin(unsigned long baud);
  void Update();
  int FindChannelValue(int channelID);
private:
  HardwareSerial& serial_;
  int channels_[16];
};

#endif