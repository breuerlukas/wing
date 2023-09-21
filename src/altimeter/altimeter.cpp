#include "altimeter.h"

Altimeter::Altimeter(float localQnh) : local_qnh_(localQnh) {

}

Altimeter::Altimeter() : Altimeter(1013.25) {

}

void Altimeter::Initialize() {
  bmp_.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  Configure();
}

void Altimeter::Configure() {
  bmp_.setSampling(Adafruit_BMP280::MODE_NORMAL, Adafruit_BMP280::SAMPLING_X2,
    Adafruit_BMP280::SAMPLING_X16, Adafruit_BMP280::FILTER_X16,
    Adafruit_BMP280::STANDBY_MS_1);
}

void Altimeter::Calibrate() {
  float accumulated = 0;
  for (int i = 0; i < 50; i++) {
    Tick();
    accumulated += current_altitude_;
  }
  home_altitude_ = accumulated / 50;
}

void Altimeter::Tick() {
  float altitude = bmp_.readAltitude(local_qnh_);
  CalculateVerticalSpeed(altitude);
  current_altitude_ = altitude;
}

float Altimeter::CalculateVerticalSpeed(float altitude) {
  long time = millis();
  current_vertical_speed = (altitude - previous_moving_average) /
    (float) ((time - previous_measurement_time) / (float) 1000);
  previous_moving_average = altitude;
  previous_measurement_time = time;
  return current_vertical_speed;
}

float Altimeter::Altitude() {
  return current_altitude_;
}

float Altimeter::RelativeAltitude() {
  return current_altitude_ - home_altitude_;
}

float Altimeter::VerticalSpeed() {
  return current_vertical_speed;
}