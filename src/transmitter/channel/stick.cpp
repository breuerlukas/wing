#include "stick.h"

Stick::Stick(int pin) : Channel(pin) {

}

void Stick::Update(long value) {
  this->value = value;
  value_ = Read();
}

int Stick::Value() {
  return value_;
}
