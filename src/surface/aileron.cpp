#include "aileron.h"

Aileron::Aileron(int servoPin) : servo_pin_(servoPin) {

}

void Aileron::Initialize() {
  servo_.attach(servo_pin_);
}

void Aileron::Move(int value) {
  if (previous_servo_value_ == value) {
    return;
  }
  servo_.write(value);
  previous_servo_value_ = value;
}