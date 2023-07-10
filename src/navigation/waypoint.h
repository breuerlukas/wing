#ifndef WING_WAYPOINT_H
#define WING_WAYPOINT_H

#include "location.h"

enum WaypointTask {
  kDeparture,
  kInFlight,
  kArrival
};

class Waypoint {
private:
  Location location_;
  double altitude_;
  WaypointTask task_;
public:
  Waypoint(Location location, double altitude, WaypointTask task);
  Location Location();
  double Altitude();
  WaypointTask Task();
};


#endif //WING_WAYPOINT_H
