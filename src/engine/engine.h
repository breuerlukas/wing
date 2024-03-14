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
  void Idle();
  void ApplyThrust(int thrust);
  void ApplyThrustPercentage(int percentage);
  int Thrust();
};


#endif //WING_ENGINE_H
