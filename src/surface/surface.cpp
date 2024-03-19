#include "surface.h"

Surface::Surface(int servoPin) : Surface(servoPin, 0) {

}

Surface::Surface(int servoPin, int trim) : servo_pin_(servoPin), trim_(trim) {

}

void Surface::Initialize() {
  servo_.attach(servo_pin_);
}

void Surface::Move(int value) {
  servo_.write(value + trim_);
}
