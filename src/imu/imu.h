#ifndef IMU_H
#define IMU_H

#include <Arduino.h>
#include <Wire.h>
#include "ICM_20948.h"

class Imu {
private:
  ICM_20948_I2C sensor_;
  float roll_;
  float pitch_;
  float acceleration_;
  void CalculateRollAndPitch(icm_20948_DMP_data_t data);
  void CalculateAcceleration(icm_20948_DMP_data_t data);
public:
  Imu();
  void Initialize();
  void Tick();
  float Roll();
  float Pitch();
  float Acceleration();
};

#endif // IMU_H