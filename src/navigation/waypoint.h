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
  WaypointTask task_;
public:
  Waypoint(Location location, Task task);
};


#endif //WING_WAYPOINT_H
