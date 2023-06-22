#include "location.h"

Location::Location(float latitude, float longitude) : latitude_(latitude), longitude_(longitude) {

}

Direction Location::DirectionTo(Location destination) {
  float teta1 = DegreesToRadians(latitude_);
  float teta2 = DegreesToRadians(destination.latitude_);
  float delta1 = DegreesToRadians(destination.latitude_ - latitude_);
  float delta2 = DegreesToRadians(destination.longitude_ - longitude_);
  float y = sin(delta2) * cos(teta2);
  float x = cos(teta1)*sin(teta2) - sin(teta1)*cos(teta2)*cos(delta2);
  float bearing = atan2(y,x);
  bearing = RadiansToDegrees(bearing);
  bearing = (((int) bearing + 360) % 360);
  return Direction(bearing, 0);
}

float Location::DegreesToRadians(float degrees) {
  return degrees * M_PI / 180.0;
}

float Location::RadiansToDegrees(float radians) {
  return radians * 180.0 / M_PI;
}

float Location::Latitude() {
  return latitude_;
}

float Location::Longitude() {
  return longitude_;
}
