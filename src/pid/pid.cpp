#include "pid.h"

Pid::Pid(float pWeight, float iWeight, float dWeight)
  : p_weight_(pWeight),
    i_weight_(iWeight),
    d_weight_(dWeight) {

}

float Pid::Calculate(float currentState, float error) {
  long time = millis();
  float elapsedTime = (float) (time - previous_time_) / 1000;
  p_value_ = p_weight_ * error;
  i_value_ = i_value_ + (i_weight_ * error);
  d_value_ = d_weight_ * ((previous_state_ - currentState) / elapsedTime);
  float pid = p_value_ + i_value_ + d_value_;
  previous_time_ = time;
  previous_state_ = currentState;
  return pid;
}