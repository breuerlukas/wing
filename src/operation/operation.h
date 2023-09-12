#ifndef WING_OPERATION_H
#define WING_OPERATION_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include <cmath>
#include "transmitter/transmitter.h"
#include "imu/imu.h"
#include "altimeter/altimeter.h"
#include "engine/engine.h"
#include "surface/surfaces.h"
#include "transmitter/channel/dual-switch.h"
#include "transmitter/channel/triple-switch.h"
#include "transmitter/channel/knob.h"
#include "limits/limits.h"
#include "pid/pid.h"

class Operation {
private:
  Transmitter* transmitter_;
  Imu* imu_;
  Altimeter* altimeter_;
  Engine* engine_;
  Surfaces* surfaces_;
  DualSwitch* engine_switch_;
  TripleSwitch* stabilization_switch_;
  Pid* roll_pid_controller_;
  Pid* pitch_pid_controller_;
  float desired_altitude_ = 0;
  long last_altitude_reset = 0;
  void ApplyEngineThrust();
  void ApplySurfaceMovement();
  float CalculateRollAngle(int aileronStickValue);
  float CalculatePitchAngle(int elevatorStickValue);
  void AdjustPlaneOrientation(float desiredRollAngle, float desiredPitchAngle);
  void AdjustPlaneRollAngle(float desiredRollAngle);
  void AdjustPlanePitchAngle(float desiredPitchAngle);
public:
  Operation(Transmitter* transmitter, Imu* imu, Altimeter* altimeter, Engine* engine,
    Surfaces* surfaces, DualSwitch* engineSwitch, TripleSwitch* stabilizationSwitch,
    Pid* rollPidController, Pid* pitchPidController);
  void Recalculate();
};

#endif //WING_OPERATION_H
