#include "knob.h"

Knob::Knob(int id) : Channel(id) {
  value = 1000;
}

int Knob::Value() {
  return value;
}