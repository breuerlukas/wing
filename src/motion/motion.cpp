#include "motion.h"

Motion::Motion() {

}

void Motion::Initialize() {
  Wire.begin();
  SetupMpu6050Registers();
}

void Motion::SetupMpu6050Registers() {
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x1A);
  Wire.write(0x03);
  Wire.endTransmission();
}

void Motion::Recalculate() {
  ReadSensors();
  CalculateGyroAngles();
  CalculateAccelerometerAngles();
}

void Motion::ReadSensors() {
  RequestData();
  while (Wire.available() < 14);
  ReadAcceleration();
  ReadTemperature();
  ReadInclination();
}

void Motion::RequestData() {
  Wire.beginTransmission(MPU_ADDRESS);
  Wire.write(0x3B);
  Wire.endTransmission();
  Wire.requestFrom(MPU_ADDRESS, 14);
}

void Motion::ReadAcceleration() {
  acceleration_raw[X] = Wire.read() << 8 | Wire.read();
  acceleration_raw[Y] = Wire.read() << 8 | Wire.read();
  acceleration_raw[Z] = Wire.read() << 8 | Wire.read();
}

void Motion::ReadTemperature() {
  temperature_ = Wire.read() << 8 | Wire.read();
}

void Motion::ReadInclination() {
  inclination_raw[X] = Wire.read() << 8 | Wire.read();
  inclination_raw[Y] = Wire.read() << 8 | Wire.read();
  inclination_raw[Z] = Wire.read() << 8 | Wire.read();
}

void Motion::CalculateAccelerometerAngles() {
  acceleration_total_vector = sqrt(pow(acceleration_raw[X], 2) + pow(acceleration_raw[Y], 2) + pow(acceleration_raw[Z], 2));
  if (abs(acceleration_raw[X]) < acceleration_total_vector) {
    acceleration_angle[X] = asin((float)acceleration_raw[Y] / acceleration_total_vector) * (180 / PI);
  }
  if (abs(acceleration_raw[Y]) < acceleration_total_vector) {
    acceleration_angle[Y] = asin((float)acceleration_raw[X] / acceleration_total_vector) * (180 / PI);
  }
}

void Motion::CalculateGyroAngles() {
  inclination_angle[X] += (inclination_raw[X] / (SAMPLING_FREQUENCY * GYRO_SENSITIVITY_SCALE_FACTOR));
  inclination_angle[Y] += (-inclination_raw[Y] / (SAMPLING_FREQUENCY * GYRO_SENSITIVITY_SCALE_FACTOR));
  inclination_angle[Y] += inclination_angle[X] * sin(inclination_raw[Z] * (PI / (SAMPLING_FREQUENCY * GYRO_SENSITIVITY_SCALE_FACTOR * 180)));
  inclination_angle[X] -= inclination_angle[Y] * sin(inclination_raw[Z] * (PI / (SAMPLING_FREQUENCY * GYRO_SENSITIVITY_SCALE_FACTOR * 180)));
}

float Motion::Roll() {
  return acceleration_angle[Y];
}

float Motion::Pitch() {
  return acceleration_angle[X];
}

int Motion::Temperature() {
  return temperature_;
}