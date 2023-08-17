#include "motion.h"

Motion::Motion() {

}

void Motion::Initialize() {
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
}

void Motion::Mahony_update(float ax, float ay, float az, float gx, float gy, float gz, float deltat) {
  float recipNorm;
  float vx, vy, vz;
  float ex, ey, ez;
  float qa, qb, qc;
  static float ix = 0.0, iy = 0.0, iz = 0.0;
  float tmp;
  tmp = ax * ax + ay * ay + az * az;
  if (tmp > 0.0) {
    recipNorm = 1.0 / sqrt(tmp);
    ax *= recipNorm;
    ay *= recipNorm;
    az *= recipNorm;
    vx = q[1] * q[3] - q[0] * q[2];
    vy = q[0] * q[1] + q[2] * q[3];
    vz = q[0] * q[0] - 0.5f + q[3] * q[3];
    ex = (ay * vz - az * vy);
    ey = (az * vx - ax * vz);
    ez = (ax * vy - ay * vx);
    if (Ki > 0.0f) {
      ix += Ki * ex * deltat;
      iy += Ki * ey * deltat;
      iz += Ki * ez * deltat;
      gx += ix;
      gy += iy;
      gz += iz;
    }
    gx += Kp * ex;
    gy += Kp * ey;
    gz += Kp * ez;
  }
  deltat = 0.5 * deltat;
  gx *= deltat;
  gy *= deltat;
  gz *= deltat;
  qa = q[0];
  qb = q[1];
  qc = q[2];
  q[0] += (-qb * gx - qc * gy - q[3] * gz);
  q[1] += (qa * gx + qc * gz - q[3] * gy);
  q[2] += (qa * gy - qb * gz + q[3] * gx);
  q[3] += (qa * gz + qb * gy - qc * gx);
  recipNorm = 1.0 / sqrt(q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);
  q[0] = q[0] * recipNorm;
  q[1] = q[1] * recipNorm;
  q[2] = q[2] * recipNorm;
  q[3] = q[3] * recipNorm;
}

void Motion::Recalculate() {
  static unsigned int i = 0;
  static float deltat = 0;
  static unsigned long now = 0, last = 0;
  static long gsum[3] = {0};
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  int16_t Tmp;
  float Axyz[3];
  float Gxyz[3];
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14);
  int t = Wire.read() << 8;
  ax = t | Wire.read();
  t = Wire.read() << 8;
  ay = t | Wire.read();
  t = Wire.read() << 8;
  az = t | Wire.read();
  t = Wire.read() << 8;
  Tmp = t | Wire.read();
  t = Wire.read() << 8;
  gx = t | Wire.read();
  t = Wire.read() << 8;
  gy = t | Wire.read();
  t = Wire.read() << 8;
  gz = t | Wire.read();
  i++;
  if (cal_gyro) {
    gsum[0] += gx; gsum[1] += gy; gsum[2] += gz;
    if (i == 500) {
      cal_gyro = 0;
      for (char k = 0; k < 3; k++) {
        G_off[k] = ((float) gsum[k]) / 500.0;
      }
    }
  } else {
    Axyz[0] = (float) ax;
    Axyz[1] = (float) ay;
    Axyz[2] = (float) az;
    for (i = 0; i < 3; i++) {
      Axyz[i] = (Axyz[i] - A_cal[i]) * A_cal[i + 3];
    }
    Gxyz[0] = ((float) gx - G_off[0]) * gscale;
    Gxyz[1] = ((float) gy - G_off[1]) * gscale;
    Gxyz[2] = ((float) gz - G_off[2]) * gscale;
    now = micros();
    deltat = (now - last) * 1.0e-6;
    last = now;
    Mahony_update(Axyz[0], Axyz[1], Axyz[2], Gxyz[0], Gxyz[1], Gxyz[2], deltat);
    roll = atan2((q[0] * q[1] + q[2] * q[3]), 0.5 - (q[1] * q[1] + q[2] * q[2]));
    pitch = asin(2.0 * (q[0] * q[2] - q[1] * q[3]));
    pitch *= 180.0 / PI;
    roll *= 180.0 / PI;
  }
}

float Motion::Roll() {
  return pitch;
}

float Motion::Pitch() {
  return roll;
}

float Motion::Temperature() {
  return 0;
}