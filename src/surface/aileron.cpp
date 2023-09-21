#include "aileron.h"

Aileron::Aileron(int servoPin) : servo_pin_(servoPin) {

}

void Aileron::Initialize() {
  servo_.attach(servo_pin_);
}

void Aileron::Move(int value) {
  servo_.write(value);
}