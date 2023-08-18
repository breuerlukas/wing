#ifndef WING_AUTOPILOT_H
#define WING_AUTOPILOT_H

#include <cmath>
#include "transmitter/transmitter.h"
#include "motion/motion.h"
#include "engine/engine.h"
#include "surface/surfaces.h"
#include "transmitter/channel/switch.h"
#include "transmitter/channel/knob.h"
#include "navigation/location.h"
#include "navigation/direction.h"
#include "navigation/waypoint.h"
#include "navigation/mission.h"
#include "limits/limits.h"

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
  Knob* roll_stabilization_knob_;
  Knob* pitch_stabilization_knob_;
  TinyGPSPlus* gps_;
  Location* plane_location_;
  Mission* mission_;
  AutopilotState state_ = kDisengaged;
  void UpdateAutopilotState();
  float CalculateRollAngle(double rollAngleDifference);
  float CalculatePitchAngle(double pitchAngleDifference);
  void AdjustPlaneOrientation(float desiredRollAngle, float desiredPitchAngle);
public:
  Autopilot(Transmitter* transmitter, Motion* motion, Engine* engine,
  Surfaces* surfaces, Switch* autopilotSwitch, Knob* rollStabilizationKnob,
  Knob* pitchStabilizationKnob, TinyGPSPlus* gps, Location* planeLocation, Mission* mission);
  void Initialize();
  void Tick();
  AutopilotState State();
};

#endif //WING_AUTOPILOT_H
