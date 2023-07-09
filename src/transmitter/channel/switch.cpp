#include "switch.h"

Switch::Switch(int pin) : Channel(pin) {

}

void Switch::Update(long value)  {
  if (value == 0) {
    return;
  }
  this->value = value;
  state_ = (value > 1500) ? kOn : kOff;
}

SwitchState Switch::State() {
  return state_;
}
