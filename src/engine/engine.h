#ifndef PLANE_ENGINE_H
#define PLANE_ENGINE_H

#include "Servo.h"

class Engine {
private:
  int esc_pin_;
  Servo esc_;
  int thrust_;
public:
  Engine(int pin);
  void Initialize();
  void ApplyThrust(int thrust);
  int Thrust();
};


#endif //PLANE_ENGINE_H
