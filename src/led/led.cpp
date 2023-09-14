#include "led.h"

Led::Led(uint8_t pin) : pin_(pin) {

}

Led::Led(uint8_t pin, int interval) : pin_(pin), current_interval_(interval) {

}

void Led::Initialize() {
  pinMode(pin_, OUTPUT);
  state_ = kOff;
  last_change_ = millis();
}

void Led::Update() {
  long time = millis();
  if (last_change_ + current_interval_ < time) {
    last_change_ = time;
    SwitchState();
    digitalWrite(pin_, state_ == kOn ? HIGH : LOW);
  }
}

void Led::SwitchState() {
  state_ = state_ == kOn ? kOff : kOn;
}

void Led::ChangeInterval(int interval) {
  current_interval_ = interval;
}

uint8_t Led::State() {
  return state_;
}