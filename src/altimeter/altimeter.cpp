#include "altimeter.h"

Altimeter::Altimeter(float localQnh) : local_qnh_(localQnh) {

}

Altimeter::Altimeter() : Altimeter(1013.25) {

}

void Altimeter::Initialize() {
  bmp_.reset();
  bmp_.begin();
}

void Altimeter::Tick() {
  uint32_t pressure = bmp_.getPressure();
  float altitude = bmp_.calAltitude(local_qnh_, pressure);
  current_altitude_ = SmoothMeasurement(altitude);
}

float Altimeter::SmoothMeasurement(float altitude) {
  if (previous_altitudes_.size() < MOVING_AVERAGE_REVIEW) {
    previous_altitudes_.push_back(altitude);
    return altitude;
  }
  if (previous_altitudes_.size() == MOVING_AVERAGE_REVIEW) {
    for (int i = 0; i < previous_altitudes_.size(); i++) {
      previous_moving_average += previous_altitudes_[i];
    }
    previous_moving_average /= previous_altitudes_.size();
    previous_altitudes_.clear();
    return previous_moving_average;
  }
  float multiplier = (float) 2 / (MOVING_AVERAGE_REVIEW + 1);
  float currentMovingAverage = (altitude - previous_moving_average) * multiplier +
    previous_moving_average;
  long time = millis();
  current_vertical_speed = (currentMovingAverage - previous_moving_average) /
    ((time - previous_measurement_time) / (float) 1000);
  previous_moving_average = currentMovingAverage;
  previous_measurement_time = time;
  return currentMovingAverage;
}

float Altimeter::Altitude() {
  return current_altitude_;
}

float Altimeter::VerticalSpeed() {
  return current_vertical_speed;
}