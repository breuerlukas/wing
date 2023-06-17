#ifndef PLANE_ELEVON_H
#define PLANE_ELEVON_H

#include <Servo.h>

class Elevon {
private:
  int servo_pin_;
  Servo servo_;
public:
  Elevon(int servo_pin);
  void Initialize();
  void Move(int value);
  bool operator <(const Elevon& elevon) const {
    return servo_pin_ < elevon.servo_pin_;
  }
};


#endif //PLANE_ELEVON_H
