#ifndef WING_LED_H
#define WING_LED_H

#include "Arduino.h"

enum LedState {
  kEnabled,
  kDisabled
};

class Led {
private:
  uint8_t pin_;
  LedState state_;
public:
  Led(uint8_t pin);
  void Initialize();
  void ChangeState(LedState state);
  uint8_t State();
};


#endif //WING_LED_H
