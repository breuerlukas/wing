#ifndef WING_AUTOPILOT_H
#define WING_AUTOPILOT_H

#include <cmath>
#include "transmitter/transmitter.h"
#include "imu/imu.h"
#include "altimeter/altimeter.h"
#include "engine/engine.h"
#include "surface/surfaces.h"
#include "transmitter/channel/dual-switch.h"
#include "transmitter/channel/triple-switch.h"
#include "pid/pid.h"
#include "navigation/location.h"
#include "navigation/direction.h"
#include "navigation/waypoint.h"
#include "navigation/mission.h"
#include "config/config.h"

enum AutopilotState {
  kEngaged,
  kDisengaged
};

class Autopilot {
private:
  Transmitter* transmitter_;
  Imu* imu_;
  Altimeter* altimeter_;
  Engine* engine_;
  Surfaces* surfaces_;
  DualSwitch* engine_switch_;
  DualSwitch* autopilot_switch_;
  TripleSwitch* autopilot_mode_switch_;
  Pid* roll_pid_controller_;
  Pid* pitch_pid_controller_;
  Location* plane_location_;
  Mission* mission_;
  AutopilotState state_ = kDisengaged;
  boolean is_interrupted_ = false;
  bool CheckAutopilotState();
  bool CheckAutopilotInterrupt();
  bool CheckWaypointReaching(double course, Direction direction);
  void UpdateAutopilotState();
  void ApplyEngineThrust();
  float CalculateRollAngle(Direction direction, double course);
  float CalculatePitchAngleManual();
  float CalculatePitchAngleAltitude();
  void AdjustPlaneOrientation(float desiredRollAngle, float desiredPitchAngle);
  void AdjustPlaneRollAngle(float desiredRollAngle);
  void AdjustPlanePitchAngle(float desiredPitchAngle);
public:
  Autopilot(Transmitter* transmitter, Imu* imu, Altimeter* altimeter, Engine* engine,
  Surfaces* surfaces, DualSwitch* engineSwitch, DualSwitch* autopilotSwitch,
  TripleSwitch* autopilotModeSwitch, Pid* rollPidController, Pid* pitchPidController,
  Location* planeLocation, Mission* mission);
  void Initialize();
  void Tick(double course);
  AutopilotState State();
};

#endif //WING_AUTOPILOT_H
