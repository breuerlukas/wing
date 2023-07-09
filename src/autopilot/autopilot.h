#ifndef WING_AUTOPILOT_H
#define WING_AUTOPILOT_H

#include "transmitter/transmitter.h"
#include "motion/motion.h"
#include "engine/engine.h"
#include "elevon/surfaces.h"
#include "transmitter/channel/switch.h"

enum AutopilotState {
  kEngaged,
  kDisengaged
};

class Autopilot {
private:
  Transmitter* transmitter_;
  Motion* motion_;
  Engine* engine_;
  Surfaces* surfaces_;
  Switch* autopilot_switch_;
  AutopilotState state_ = kDisengaged;
public:
  Autopilot(Transmitter* transmitter, Motion* motion, Engine* engine,
  Surfaces* surfaces, Switch* autopilotSwitch);
  void Initialize();
  void Tick();
  AutopilotState State();
};

#endif //WING_AUTOPILOT_H
