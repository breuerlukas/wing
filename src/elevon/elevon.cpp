#include "elevon.h"

Elevon::Elevon(int servo_pin) : servo_pin_(servo_pin) {

}

void Elevon::Initialize() {
  servo_.attach(servo_pin_);
}

void Elevon::Move(int value) {
  servo_.write(value);
}
