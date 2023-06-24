#include "stick.h"

Stick::Stick(int id) : Channel(id) {
  value = 1500;
}

int Stick::Value() {
  return value;
}
