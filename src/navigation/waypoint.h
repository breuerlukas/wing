#ifndef WING_WAYPOINT_H
#define WING_WAYPOINT_H

#include "location.h"

class Waypoint {
private:
  Location location_;
  double altitude_;
public:
  Waypoint(Location location, double altitude);
  Location Location();
  double Altitude();
};


#endif //WING_WAYPOINT_H
