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