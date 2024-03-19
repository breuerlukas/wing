#ifndef WING_SURFACE_H
#define WING_SURFACE_H

#include "PWMServo.h"

class Surface {
private:
  int servo_pin_;
  int trim_;
  PWMServo servo_;
public:
  Surface(int servoPin);
  Surface(int servoPin, int trim);
  void Initialize();
  void Move(int value);
};

#endif //WING_SURFACE_H
