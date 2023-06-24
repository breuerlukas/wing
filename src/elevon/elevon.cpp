#include "elevon.h"

Elevon::Elevon(int servoPin) : servo_pin_(servoPin) {

}

void Elevon::Initialize() {
  servo_.attach(servo_pin_);
}

void Elevon::Move(int value) {
  servo_.write(value);
}
