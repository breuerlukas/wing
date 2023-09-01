#include "dual-switch.h"

DualSwitch::DualSwitch(int pin) : Channel(pin) {

}

void DualSwitch::Update(long value)  {
  if (value == 0) {
    return;
  }
  this->value = value;
  state_ = (value > 1500) ? kOn : kOff;
}

DualSwitchState DualSwitch::State() {
  return state_;
}
