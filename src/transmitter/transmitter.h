#ifndef PLANE_TRANSMITTER_H
#define PLANE_TRANSMITTER_H

#include "ArduinoSTL.h"
#include "channel/channel.h"
#include "channel/stick.h"

class Transmitter {
private:
  Stick* throttle_stick_;
  Stick* elevator_stick_;
  Stick* aileron_stick_;
  std::vector<Channel*> channels_;
public:
  Transmitter(Stick* throttle_stick, Stick* elevator_stick, Stick* aileron_stick);
  void Initialize();
  void Update();
  Stick* ThrottleStick();
  Stick* ElevatorStick();
  Stick* AileronStick();
};


#endif //PLANE_TRANSMITTER_H
