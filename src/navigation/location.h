#ifndef WING_LOCATION_H
#define WING_LOCATION_H

#include <cmath>
#include <TinyGPSPlus.h>
#include "direction.h"

class Location {
private:
  double latitude_;
  double longitude_;
public:
  Location(double latitude, double longitude);
  void Update(Location otherLocation);
  void Update(double latitude, double longitude);
  Direction DirectionTo(Location destination);
  double Latitude();
  double Longitude();
  bool IsEquals(Location otherLocation);
};


#endif //WING_LOCATION_H
