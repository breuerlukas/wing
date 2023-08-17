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
  channels_.push_back(channel);
}

void Transmitter::Initialize() {
  bus_.begin(Serial);
}

void Transmitter::Update() {
  for (int i = 0; i < channels_.size(); i++) {
    channels_[i]->Update(bus_.readChannel(channels_[i]->Id()));
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
  channels_.erase(std::remove(channels_.begin(), channels_.end(), channel),
    channels_.end());
}
