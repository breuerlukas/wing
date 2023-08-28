#ifndef WING_PID_H
#define WING_PID_H

#include "Arduino.h"

class Pid {
private:
  float p_weight_;
  float i_weight_;
  float d_weight_;
  long previous_time_;
  float previous_error_;
  float p_value_;
  float i_value_;
  float d_value_;
public:
  Pid(float pWeight, float iWeight, float dWeight);
  float Calculate(float error);
};


#endif //WING_PID_H
