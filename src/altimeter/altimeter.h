#ifndef WING_ALTIMETER_H
#define WING_ALTIMETER_H

#include "ArduinoSTL.h"
#include "DFRobot_BMP280.h"
#include "Wire.h"

#define MOVING_AVERAGE_REVIEW 10
typedef DFRobot_BMP280_IIC BMP;

class Altimeter {
private:
  BMP bmp_ = BMP(&Wire, BMP::eSdoLow);
  float local_qnh_;
  std::vector<float> previous_altitudes_;
  float current_altitude_;
  float current_vertical_speed;
  float previous_moving_average;
  long previous_measurement_time;
  float SmoothMeasurement(float altitude);
public:
  Altimeter(float localQnh);
  Altimeter();
  void Initialize();
  void Tick();
  float Altitude();
  float VerticalSpeed();
};


#endif //WING_ALTIMETER_H
