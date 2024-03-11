#ifndef WING_ALTIMETER_H
#define WING_ALTIMETER_H

#include "Adafruit_BMP280.h"
#include "Wire.h"
#include "config/config.h"

const float kDefaultQnh = 1013.25;

class Altimeter {
private:
  Adafruit_BMP280 bmp_ = Adafruit_BMP280(&Wire1);
  float local_qnh_;
  float home_altitude_;
  float current_altitude_;
  float current_vertical_speed;
  float previous_moving_average;
  long previous_measurement_time;
  void Configure();
  float CalculateVerticalSpeed(float altitude);
public:
  Altimeter(float localQnh);
  Altimeter();
  void Initialize();
  void Calibrate();
  void Tick();
  float Altitude();
  float RelativeAltitude();
  float VerticalSpeed();
};


#endif //WING_ALTIMETER_H
