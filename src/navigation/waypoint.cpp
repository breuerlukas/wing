#include "waypoint.h"

Waypoint::Waypoint(class Location location, double altitude)
  : location_(location),
    altitude_(altitude) {

}

Location Waypoint::Location() {
  return location_;
}

double Waypoint::Altitude() {
  return altitude_;
}

bool Waypoint::IsEquals(Waypoint otherWaypoint) {
  return location_.IsEquals(otherWaypoint.Location()) &&
    altitude_ == otherWaypoint.Altitude();
}
