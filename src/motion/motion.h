#ifndef WING_MOTION_H
#define WING_MOTION_H

#include <cmath>
#include <Arduino.h>
#include "Wire.h"

#define X 0
#define Y 1
#define Z 2

#define MPU_ADDRESS 0x68
#define SAMPLING_FREQUENCY 250
#define GYRO_SENSITIVITY_SCALE_FACTOR 65.5

class Motion {
private:
  long acceleration_total_vector;
  int acceleration_raw[3] = {0 , 0 , 0};
  float acceleration_angle[3] = {0, 0, 0};
  int inclination_raw[3] = {0, 0, 0};
  float inclination_angle[3]  = {0, 0, 0};
  int temperature_;
  void SetupMpu6050Registers();
  void ReadSensors();
  void RequestData();
  void ReadAcceleration();
  void ReadTemperature();
  void ReadInclination();
  void CalculateAccelerometerAngles();
  void CalculateGyroAngles();
public:
  Motion();
  void Initialize();
  void Recalculate();
  float Roll();
  float Pitch();
  int Temperature();
};


#endif //WING_MOTION_H