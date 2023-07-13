#ifndef WING_AUTOPILOT_H
#define WING_AUTOPILOT_H

#include "transmitter/transmitter.h"
#include "motion/motion.h"
#include "engine/engine.h"
#include "elevon/surfaces.h"
#include "transmitter/channel/switch.h"
#include "navigation/location.h"
#include "navigation/direction.h"
#include "navigation/waypoint.h"
#include "navigation/mission.h"

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
  Location* plane_location_;
  Mission* mission_;
  AutopilotState state_ = kDisengaged;
  void UpdateAutopilotState();
public:
  Autopilot(Transmitter* transmitter, Motion* motion, Engine* engine,
  Surfaces* surfaces, Switch* autopilotSwitch, Location* planeLocation, Mission* mission);
  void Initialize();
  void Tick();
  AutopilotState State();
};

#endif //WING_AUTOPILOT_H
