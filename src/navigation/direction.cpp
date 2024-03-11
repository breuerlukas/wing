#include "direction.h"

Direction::Direction(double bearing, double distance)
  : bearing_(bearing), distance_(distance) {

}

double Direction::Bearing() {
  return bearing_;
}

double Direction::Distance() {
  return distance_;
}

bool Direction::IsEquals(Direction otherDirection) {
  return bearing_ == otherDirection.Bearing() &&
    distance_ == otherDirection.Distance();
}
