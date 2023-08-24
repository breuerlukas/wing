#ifndef WING_RUDDERVATOR_H
#define WING_RUDDERVATOR_H

#include "Servo.h"

class Ruddervator {
private:
  int servo_pin_;
  Servo servo_;
public:
  Ruddervator(int servoPin);
  void Initialize();
  void Move(int value);
};


#endif //WING_RUDDERVATOR_H
