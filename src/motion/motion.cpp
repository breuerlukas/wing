#include "motion.h"

Motion::Motion() {

}

void Motion::Initialize() {
  Wire.begin();
  mpu_.begin();
  mpu_.calcOffsets(true,true);
}

void Motion::Recalculate() {
  mpu_.update();
}

float Motion::Roll() {
  return mpu_.getAngleY();
}

float Motion::Pitch() {
  return mpu_.getAngleX();
}

float Motion::Temperature() {
  return mpu_.getTemp();
}