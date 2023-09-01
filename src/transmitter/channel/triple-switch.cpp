#include "triple-switch.h"

TripleSwitch::TripleSwitch(int pin) : Channel(pin) {

}

void TripleSwitch::Update(long value)  {
  if (value == 0) {
    return;
  }
  this->value = value;
  if (value < 1200) {
    state_ = kUp;
    return;
  }
  if (value >= 1200 && value <= 1800) {
    state_ = kMiddle;
    return;
  }
  if (value > 1800) {
    state_ = kDown;
  }
}

TripleSwitchState TripleSwitch::State() {
  return state_;
}