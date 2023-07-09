#ifndef PLANE_WAYPOINT_H
#define PLANE_WAYPOINT_H

#include "location.h"

enum WaypointTask {
  kDeparture,
  kInFlight,
  kArrival
};

class Waypoint {
private:
  Location location_;
  WaypointTask task_;
public:
  Waypoint(Location location, Task task);
};


#endif //PLANE_WAYPOINT_H
