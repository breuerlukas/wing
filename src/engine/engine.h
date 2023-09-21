#ifndef WING_ENGINE_H
#define WING_ENGINE_H

#include "Arduino.h"
#include "PWMServo.h"

class Engine {
private:
  int esc_pin_;
  PWMServo esc_;
  int thrust_;
public:
  Engine(int pin);
  void Initialize();
  void ApplyThrust(int thrust);
  int Thrust();
};


#endif //WING_ENGINE_H
