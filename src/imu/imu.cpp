#include "imu.h"

Imu::Imu() {

}

void Imu::Initialize() {
  Wire.begin();
  Wire.setClock(400000);
  sensor_.begin(Wire, 1);
  bool success = true;
  success &= (sensor_.initializeDMP() == ICM_20948_Stat_Ok);
  success &= (sensor_.enableDMPSensor(INV_ICM20948_SENSOR_GAME_ROTATION_VECTOR) == ICM_20948_Stat_Ok);
  success &= (sensor_.setDMPODRrate(DMP_ODR_Reg_Quat6, 0) == ICM_20948_Stat_Ok);
  success &= (sensor_.enableDMPSensor(INV_ICM20948_SENSOR_LINEAR_ACCELERATION) == ICM_20948_Stat_Ok);
  success &= (sensor_.setDMPODRrate(DMP_ODR_Reg_Accel, 0) == ICM_20948_Stat_Ok);
  success &= (sensor_.enableFIFO() == ICM_20948_Stat_Ok);
  success &= (sensor_.enableDMP() == ICM_20948_Stat_Ok);
  success &= (sensor_.resetDMP() == ICM_20948_Stat_Ok);
  success &= (sensor_.resetFIFO() == ICM_20948_Stat_Ok);
  if (!success) {
    Serial.println("IMU initialization failed");
    Serial.println("Please check that you have uncommented line 29 (#define ICM_20948_USE_DMP) in ICM_20948_C.h...");
    while (true) {
    }
  }
}

void Imu::Tick() {
  icm_20948_DMP_data_t data;
  sensor_.readDMPdataFromFIFO(&data);
  if (!((sensor_.status == ICM_20948_Stat_Ok) || (sensor_.status == ICM_20948_Stat_FIFOMoreDataAvail))) {
    return;
  }
  if ((data.header & DMP_header_bitmap_Quat6) <= 0) {
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
  double qw = q0;
  double qx = q2;
  double qy = q1;
  double qz = -q3;
  double t0 = +2.0 * (qw * qx + qy * qz);
  double t1 = +1.0 - 2.0 * (qx * qx + qy * qy);
  roll_ = atan2(t0, t1) * 180.0 / PI;
  double t2 = +2.0 * (qw * qy - qx * qz);
  t2 = t2 > 1.0 ? 1.0 : t2;
  t2 = t2 < -1.0 ? -1.0 : t2;
  pitch_ = asin(t2) * 180.0 / PI;
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
