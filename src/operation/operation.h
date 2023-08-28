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
#include "transmitter/channel/switch.h"
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
  Switch* engine_switch_;
  Switch* stabilization_switch_;
  Switch* pitch_stabilization_switch_;
  Knob* roll_stabilization_knob_;
  Knob* pitch_stabilization_knob_;
  Pid* roll_pid_controller_;
  Pid* pitch_pid_controller_;
  void ApplyEngineThrust();
  void ApplySurfaceMovement();
  float CalculateRollAngle(int aileronStickValue);
  float CalculatePitchAngle(int elevatorStickValue);
  //void AdjustPlaneOrientation(float desiredRollAngle, float desiredPitchAngle);
  void AdjustPlaneRollAngle(float desiredRollAngle);
  //void AdjustPlanePitchAngle(float desiredPitchAngle);
public:
  Operation(Transmitter* transmitter, Imu* imu, Altimeter* altimeter, Engine* engine,
    Surfaces* surfaces, Switch* engineSwitch, Switch* stabilizationSwitch,
    Switch* pitchStabilizationSwitch, Knob* rollStabilizationKnob,
    Knob* pitchStabilizationKnob, Pid* rollPidController, Pid* pitchPidController);
  void Recalculate();
};

#endif //WING_OPERATION_H
