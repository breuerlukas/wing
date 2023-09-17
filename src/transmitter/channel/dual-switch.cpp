#include "dual-switch.h"

DualSwitch::DualSwitch(int pin) : Channel(pin) {

}

void DualSwitch::Update(long value)  {
  if (value < 1000 || value > 2000) {
    return;
  }
  this->value = value;
  DualSwitchState newState = FindState(value);
  if (is_state_changing_) {
    state_ = newState;
    is_state_changing_ = false;
    return;
  }
  if (state_ != newState) {
    is_state_changing_ = true;
    return;
  }
  state_ = newState;
}

DualSwitchState DualSwitch::FindState(long value) {
  return (value > 1500) ? kOn : kOff;
}

DualSwitchState DualSwitch::State() {
  return state_;
}
