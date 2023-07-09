#include "autopilot.h"

Autopilot::Autopilot(Transmitter* transmitter, Motion* motion, Engine* engine,
  Surfaces* surfaces, Switch* autopilotSwitch)
  : transmitter_(transmitter),
    motion_(motion),
    engine_(engine),
    surfaces_(surfaces),
    autopilot_switch_(autopilotSwitch) {

}

void Autopilot::Initialize() {

}

void Autopilot::Tick() {

}

AutopilotState Autopilot::State() {
  return state_;
}