#include "autopilot.h"

Autopilot::Autopilot(Transmitter* transmitter, Motion* motion, Engine* engine,
  Surfaces* surfaces, Switch* autopilotSwitch, Location* planeLocation, Mission* mission)
  : transmitter_(transmitter),
    motion_(motion),
    engine_(engine),
    surfaces_(surfaces),
    autopilot_switch_(autopilotSwitch),
    plane_location_(planeLocation),
    mission_(mission) {

}

void Autopilot::Initialize() {

}

void Autopilot::Tick() {
  UpdateAutopilotState();
  if (state_ == kDisengaged) {
    return;
  }
}

void Autopilot::UpdateAutopilotState() {
  state_ = autopilot_switch_->State() == kOn ? kEngaged : kDisengaged;
}

AutopilotState Autopilot::State() {
  return state_;
}