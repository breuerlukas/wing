#ifndef WING_MOTION_H
#define WING_MOTION_H

#include <Arduino.h>
#include "Wire.h"

#define gscale ((250./32768.0)*(PI/180.0))

class Motion {
private:
  int MPU_addr = 0x68;
  int cal_gyro = 1;
  float A_cal[6] = {265.0, -80.0, -700.0, 0.994, 1.000, 1.014};
  float G_off[3] = { 0., 0., 0.};
  float q[4] = {1.0, 0.0, 0.0, 0.0};
  float Kp = 15;
  float Ki = 0.0;
  float pitch, roll;
  void Mahony_update(float ax, float ay, float az, float gx, float gy, float gz, float deltat);
public:
  Motion();
  void Initialize();
  void Recalculate();
  float Roll();
  float Pitch();
  float Temperature();
};


#endif //WING_MOTION_H