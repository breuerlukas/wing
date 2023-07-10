#ifndef WING_LOCATION_H
#define WING_LOCATION_H

#include <cmath>
#include "direction.h"

class Location {
private:
  float latitude_;
  float longitude_;
  float DegreesToRadians(float degrees);
  float RadiansToDegrees(float radians);
public:
  Location(float latitude, float longitude);
  Direction DirectionTo(Location destination);
  float Latitude();
  float Longitude();
};


#endif //WING_LOCATION_H
