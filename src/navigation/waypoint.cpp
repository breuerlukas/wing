#include "waypoint.h"

Waypoint::Waypoint(class Location location, double altitude)
  : Waypoint(location, altitude, nullptr) {

}

Waypoint::Waypoint(class Location location, double altitude,
  Waypoint* followingWaypoint)
  : location_(location),
    altitude_(altitude),
    following_waypoint_(followingWaypoint) {

}

Location Waypoint::Location() {
  return location_;
}

double Waypoint::Altitude() {
  return altitude_;
}

bool Waypoint::HasFollowingWaypoint() {
  return following_waypoint_ != nullptr;
}

Waypoint* Waypoint::FollowingWaypoint() {
  return following_waypoint_;
}

bool Waypoint::IsEquals(Waypoint otherWaypoint) {
  return location_.IsEquals(otherWaypoint.Location()) &&
    altitude_ == otherWaypoint.Altitude();
}
