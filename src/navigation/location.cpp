#include "location.h"

Location::Location(double latitude, double longitude) : latitude_(latitude), longitude_(longitude) {

}

void Location::Update(Location otherLocation) {
  Update(otherLocation.Latitude(), otherLocation.Longitude());
}

void Location::Update(double latitude, double longitude) {
  latitude_ = latitude;
  longitude_ = longitude;
}

Direction Location::DirectionTo(Location destination) {
  double course = TinyGPSPlus::courseTo(latitude_, longitude_,
    destination.Latitude(), destination.Longitude());
  double distance = TinyGPSPlus::distanceBetween(latitude_, longitude_,
    destination.Latitude(), destination.Longitude());
  return Direction(course, distance);
}

double Location::Latitude() {
  return latitude_;
}

double Location::Longitude() {
  return longitude_;
}

bool Location::IsEquals(Location otherLocation) {
  return latitude_ == otherLocation.Latitude() &&
    longitude_ == otherLocation.Longitude();
}
