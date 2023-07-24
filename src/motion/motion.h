#ifndef WING_MOTION_H
#define WING_MOTION_H

#include <Arduino.h>
#include "Wire.h"
#include <MPU6050_light.h>

class Motion {
private:
  MPU6050 mpu_ = MPU6050(Wire);
public:
  Motion();
  void Initialize();
  void Recalculate();
  float Roll();
  float Pitch();
  float Temperature();
};


#endif //WING_MOTION_H