#include "ruddervator.h"

Ruddervator::Ruddervator(int servoPin) : servo_pin_(servoPin) {

}

void Ruddervator::Initialize() {
  servo_.attach(servo_pin_);
}

void Ruddervator::Move(int value) {
  servo_.writeAngle(value);
}