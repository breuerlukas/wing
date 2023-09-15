#include "led.h"

Led::Led(uint8_t pin) : pin_(pin) {

}

void Led::Initialize() {
  state_ = kDisabled;
  pinMode(pin_, OUTPUT);
}

void Led::ChangeState(LedState state) {
  state_ = state;
  digitalWrite(pin_, state_ == kEnabled ? HIGH : LOW);
}

uint8_t Led::State() {
  return state_;
}