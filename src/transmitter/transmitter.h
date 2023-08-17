#ifndef WING_TRANSMITTER_H
#define WING_TRANSMITTER_H

#include <cstddef>
#include <IBusBM.h>
#include "ArduinoSTL.h"
#include "channel/channel.h"
#include "channel/stick.h"

class Transmitter {
private:
  IBusBM bus_;
  Stick* throttle_stick_;
  Stick* elevator_stick_;
  Stick* aileron_stick_;
  Stick* rudder_stick_;
  std::vector<Channel*> channels_;
public:
  Transmitter(Stick* throttleStick, Stick* elevatorStick, Stick* aileronStick,
    Stick* rudderStick);
  void RegisterChannel(Channel* channel);
  void Initialize();
  void Update();
  Stick* ThrottleStick();
  Stick* ElevatorStick();
  Stick* AileronStick();
  Stick* RudderStick();
  void RemoveChannel(Channel* channel);
};


#endif //WING_TRANSMITTER_H
