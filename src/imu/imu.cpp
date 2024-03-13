#include "imu.h"

Imu::Imu() {

}

void Imu::Initialize() {
  Wire.begin();
  Wire.setClock(400000);
  sensor_.begin(Wire, 1);
  sensor_.initializeDMP();
  sensor_.enableDMPSensor(INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR);
  sensor_.setDMPODRrate(DMP_ODR_Reg_Quat6, 0);
  sensor_.enableDMPSensor(INV_ICM20948_SENSOR_LINEAR_ACCELERATION);
  sensor_.setDMPODRrate(DMP_ODR_Reg_Accel, 0);
  sensor_.enableFIFO();
  sensor_.enableDMP();
  sensor_.resetDMP();
  sensor_.resetFIFO();
}

void Imu::Tick() {
  icm_20948_DMP_data_t data;
  sensor_.readDMPdataFromFIFO(&data);
  if (!((sensor_.status == ICM_20948_Stat_Ok) || (sensor_.status == ICM_20948_Stat_FIFOMoreDataAvail))) {
    return;
  }
  CalculateRollAndPitch(data);
  CalculateAcceleration(data);
}

void Imu::CalculateRollAndPitch(icm_20948_DMP_data_t data) {
  double q1 = ((double)data.Quat6.Data.Q1) / 1073741824.0;
  double q2 = ((double)data.Quat6.Data.Q2) / 1073741824.0;
  double q3 = ((double)data.Quat6.Data.Q3) / 1073741824.0;
  double q0 = sqrt(1.0 - ((q1 * q1) + (q2 * q2) + (q3 * q3)));
  double q2sqr = q2 * q2;
  double t0 = +2.0 * (q0 * q1 + q2 * q3);
  double t1 = +1.0 - 2.0 * (q1 * q1 + q2sqr);
  pitch_ = (float) -(atan2(t0, t1) * 180.0 / PI);
  double t2 = +2.0 * (q0 * q2 - q3 * q1);
  t2 = t2 > 1.0 ? 1.0 : t2;
  t2 = t2 < -1.0 ? -1.0 : t2;
  roll_ = (float) -(asin(t2) * 180.0 / PI);
}

void Imu::CalculateAcceleration(icm_20948_DMP_data_t data) {
  double x = data.Raw_Accel.Data.X;
  double y = data.Raw_Accel.Data.Y;
  double z = data.Raw_Accel.Data.Z;
  acceleration_ = fabs(fabs(x) + fabs(y) + fabs(z) - 10000);
}

float Imu::Roll() {
  return roll_;
}

float Imu::Pitch(){
  return pitch_;
}

float Imu::Acceleration() {
  return acceleration_;
}
