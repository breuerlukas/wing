#ifndef WING_PID_H
#define WING_PID_H

#include "Arduino.h"

class Pid {
private:
  float p_weight_;
  float i_weight_;
  float d_weight_;
  long previous_time_ = 0;
  float previous_state_ = 0;
  float previous_error_ = 0;
  float previous_value_ = 0;
  float p_value_ = 0;
  float i_value_ = 0;
  float d_value_ = 0;
public:
  Pid(float pWeight, float iWeight, float dWeight);
  float Calculate(float currentState, float error);
};


#endif //WING_PID_H
