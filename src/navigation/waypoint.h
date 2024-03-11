#ifndef WING_WAYPOINT_H
#define WING_WAYPOINT_H

#include "location.h"

class Waypoint {
private:
  Location location_;
  double altitude_;
  Waypoint* following_waypoint_;
public:
  Waypoint(Location location, double altitude);
  Waypoint(Location location, double altitude, Waypoint* followingWaypoint);
  Location Location();
  double Altitude();
  bool HasFollowingWaypoint();
  Waypoint* FollowingWaypoint();
  bool IsEquals(Waypoint otherDirection);
};


#endif //WING_WAYPOINT_H
