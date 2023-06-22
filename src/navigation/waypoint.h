#ifndef PLANE_WAYPOINT_H
#define PLANE_WAYPOINT_H

#include "location.h"

enum Task {
  kDeparture,
  kInFlight,
  kArrival
};

class Waypoint {
private:
  Location location_;
  Task task_;
public:
  Waypoint(Location location, Task task);
};


#endif //PLANE_WAYPOINT_H
