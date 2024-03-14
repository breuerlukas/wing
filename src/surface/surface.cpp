#include "surface.h"

Surface::Surface(int servoPin) : servo_pin_(servoPin) {

}

void Surface::Initialize() {
  servo_.attach(servo_pin_);
}

void Surface::Move(int value) {
  servo_.write(value);
}