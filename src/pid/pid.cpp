#include "pid.h"

Pid::Pid(float pWeight, float iWeight, float dWeight)
  : p_weight_(pWeight),
    i_weight_(iWeight),
    d_weight_(dWeight) {

}

float Pid::Calculate(float error) {
  long time = millis();
  long elapsedTime = (time - previous_time_) / 1000;
  p_value_ = p_weight_ * error;
  i_value_ = i_value_ + (i_weight_ * error);;
  d_value_ = d_weight_ * ((previous_error_ - error) / elapsedTime);
  previous_time_ = time;
  previous_error_ = error;
  return p_value_ + i_value_ + d_value_;
}