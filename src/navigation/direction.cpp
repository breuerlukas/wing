#include "direction.h"

Direction::Direction(double bearing, double distance) : bearing_(bearing), distance_(distance) {

}

double Direction::Bearing() {
  return bearing_;
}

double Direction::Distance() {
  return distance_;
}
