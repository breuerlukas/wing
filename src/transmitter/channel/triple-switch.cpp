#include "triple-switch.h"

TripleSwitch::TripleSwitch(int pin) : Channel(pin) {

}

void TripleSwitch::Update(long value)  {
  if (value < 1000 || value > 2000) {
    return;
  }
  this->value = value;
  TripleSwitchState newState = FindState(value);
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

TripleSwitchState TripleSwitch::FindState(long value) {
  if (value < 1200) {
    return kUp;
  }
  if (value >= 1200 && value <= 1800) {
    return kMiddle;
  }
  if (value > 1800) {
    return kDown;
  }
}

TripleSwitchState TripleSwitch::State() {
  return state_;
}