#include "transmitter.h"

Transmitter::Transmitter(Stick* throttleStick, Stick* elevatorStick,
  Stick* aileronStick, Stick* rudderStick)
  : throttle_stick_(throttleStick),
    elevator_stick_(elevatorStick),
    aileron_stick_(aileronStick),
    rudder_stick_(rudderStick) {
  RegisterChannel(throttleStick);
  RegisterChannel(elevatorStick);
  RegisterChannel(aileronStick);
  RegisterChannel(rudderStick);
}

void Transmitter::RegisterChannel(Channel* channel) {
  channels_.add(channel);
}

void Transmitter::Initialize() {
  crsf_.Begin(115200);
}

void Transmitter::Update() {
  crsf_.Update();
  for (int i = 0; i < channels_.size(); i++) {
    channels_.get(i)->Update(crsf_.FindChannelValue(channels_.get(i)->Id() + 1));
  }
}

Stick* Transmitter::ThrottleStick() {
  return throttle_stick_;
}

Stick* Transmitter::ElevatorStick() {
  return elevator_stick_;
}

Stick* Transmitter::AileronStick() {
  return aileron_stick_;
}
Stick* Transmitter::RudderStick() {
  return rudder_stick_;
}

void Transmitter::RemoveChannel(Channel* channel) {
  channels_.remove(channels_.searchNext(channel));
}