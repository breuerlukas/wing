#include "ruddervator.h"

Ruddervator::Ruddervator(int servoPin) : servo_pin_(servoPin) {

}

void Ruddervator::Initialize() {
  servo_.attach(servo_pin_);
}

void Ruddervator::Move(int value) {
  if (previous_servo_value_ == value) {
    return;
  }
  servo_.write(value);
  previous_servo_value_ = value;
}