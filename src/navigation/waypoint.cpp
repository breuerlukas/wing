#include "waypoint.h"

Waypoint::Waypoint(class Location location, double altitude, WaypointTask task)
  : location_(location),
    altitude_(altitude),
    task_(task) {

}

Location Waypoint::Location() {
  return location_;
}

double Waypoint::Altitude() {
  return altitude_;
}

WaypointTask Waypoint::Task() {
  return task_;
}