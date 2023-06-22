#include "direction.h"

Direction::Direction(float bearing, double distance) : bearing_(bearing), distance_(distance) {

}

float Direction::Bearing() {
  return bearing_;
}

double Direction::Distance() {
  return distance_;
}
