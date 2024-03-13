#ifndef WING_AUTOPILOT_H
#define WING_AUTOPILOT_H

#include <cmath>
#include "transmitter/transmitter.h"
#include "altimeter/altimeter.h"
#include "engine/engine.h"
#include "transmitter/channel/dual-switch.h"
#include "transmitter/channel/triple-switch.h"
#include "navigation/location.h"
#include "navigation/direction.h"
#include "navigation/waypoint.h"
#include "navigation/mission.h"
#include "operation/operation.h"
#include "autopilot/autolaunch.h"
#include "autopilot/autoland.h"
#include "config/config.h"

enum AutoPilotState {
  kAutoPilotEngaged,
  kAutoPilotDisengaged
};

class AutoPilot {
private:
  Transmitter* transmitter_;
  Altimeter* altimeter_;
  Engine* engine_;
  DualSwitch* autopilot_switch_;
  TripleSwitch* autopilot_mode_switch_;
  Location* plane_location_;
  Mission* mission_;
  Operation* operation_;
  AutoLaunch* auto_launch_;
  AutoLand* auto_land_;
  AutoPilotState state_ = kAutoPilotDisengaged;
  boolean is_interrupted_ = false;
  bool CheckAutopilotState();
  bool CheckAutopilotInterrupt();
  bool CheckWaypointReaching(double course, Direction direction);
  void UpdateAutopilotState();
  float CalculateRollAngle(Direction direction, double course);
  float CalculatePitchAngle();
public:
  AutoPilot(Transmitter* transmitter, Altimeter* altimeter, Engine* engine,
    DualSwitch* autopilotSwitch, TripleSwitch* autopilotModeSwitch,
    Location* planeLocation, Mission* mission, Operation* operation,
    AutoLaunch* autoLaunch, AutoLand* autoLand);
  void Initialize();
  void Tick(double course);
  AutoPilotState State();
};

#endif //WING_AUTOPILOT_H
