#include "switch.h"

Switch::Switch(int pin) : Channel(pin) {

}

void Switch::Update(long value)  {
  this->value = value;
  state_ = (Read() > 0) ? kOn : kOff;
}

State Switch::State() {
  return state_;
}
