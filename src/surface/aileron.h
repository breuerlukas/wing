#ifndef WING_AILERON_H
#define WING_AILERON_H

#include "PWMServo.h"

class Aileron {
private:
  int servo_pin_;
  PWMServo servo_;
public:
  Aileron(int servoPin);
  void Initialize();
  void Move(int value);
};


#endif //WING_AILERON_H
