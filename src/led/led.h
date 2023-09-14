#ifndef WING_LED_H
#define WING_LED_H

#include "Arduino.h"

enum State {
  kOn,
  kOff
};

class Led {
private:
  uint8_t pin_;
  State state_;
  int current_interval_;
  long last_change_;
  void SwitchState();
public:
  Led(uint8_t pin);
  Led(uint8_t pin, int interval);
  void Initialize();
  void Update();
  void ChangeInterval(int interval);
  uint8_t State();
};


#endif //WING_LED_H
