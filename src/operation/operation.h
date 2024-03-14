#ifndef WING_OPERATION_H
#define WING_OPERATION_H

#include <cmath>
#include "transmitter/transmitter.h"
#include "imu/imu.h"
#include "altimeter/altimeter.h"
#include "engine/engine.h"
#include "surface/surfaces.h"
#include "transmitter/channel/dual-switch.h"
#include "transmitter/channel/triple-switch.h"
#include "config/config.h"
#include "pid/pid.h"

class Operation {
private:
  Transmitter* transmitter_;
  Imu* imu_;
  Engine* engine_;
  Surfaces* surfaces_;
  DualSwitch* engine_switch_;
  TripleSwitch* stabilization_switch_;
  Pid* roll_pid_controller_;
  Pid* pitch_pid_controller_;
  int CalculateTrueRollAngle(float desiredRollAngle);
  int CalculateTruePitchAngle(float desiredPitchAngle);
  void ApplyRudderMovement();
  void ApplyManualSurfaceMovement();
  void ApplySemiSupportedSurfaceMovement();
  void ApplyFullSupportedSurfaceMovement();
public:
  Operation(Transmitter* transmitter, Imu* imu, Engine* engine,
    Surfaces* surfaces, DualSwitch* engineSwitch, TripleSwitch* stabilizationSwitch,
    Pid* rollPidController, Pid* pitchPidController);
  void Recalculate();
  void ApplyEngineThrust();
  void ApplySurfaceMovement();
  float CalculateDesiredRollAngle(int aileronStickValue);
  float CalculateDesiredPitchAngle(int elevatorStickValue);
  void AdjustPlaneOrientation(float desiredRollAngle, float desiredPitchAngle);
  void AdjustPlaneRollAngle(float desiredRollAngle);
  void AdjustPlanePitchAngle(float desiredPitchAngle);
};

#endif //WING_OPERATION_H
