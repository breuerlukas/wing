#ifndef WING_OPERATION_H
#define WING_OPERATION_H

//#define MAX(x, y) (((x) > (y)) ? (x) : (y))
//#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include <cmath>
#include "transmitter/transmitter.h"
#include "motion/motion.h"
#include "motion/imu.h"
#include "engine/engine.h"
#include "surface/surfaces.h"
#include "transmitter/channel/switch.h"
#include "transmitter/channel/knob.h"
#include "limits/limits.h"

class Operation {
private:
  Transmitter* transmitter_;
  //Motion* motion_;
  Imu* imu_;
  Engine* engine_;
  Surfaces* surfaces_;
  Switch* engine_switch_;
  Switch* stabilization_switch_;
  Switch* pitch_stabilization_switch_;
  Knob* roll_stabilization_knob_;
  Knob* pitch_stabilization_knob_;
  float elapsedTime, time, timePrev;
  float PID, previous_error, previous_desired_roll;
  float pid_p=0;
  float pid_i=0;
  float pid_d=0;
  double kp=1;
  double ki=0;
  double kd=0.1;
  void ApplyEngineThrust();
  void ApplySurfaceMovement();
  float CalculateRollAngle(int aileronStickValue);
  float CalculatePitchAngle(int elevatorStickValue);
  //void AdjustPlaneOrientation(float desiredRollAngle, float desiredPitchAngle);
  void AdjustPlaneRollAngle(float desiredRollAngle);
  //void AdjustPlanePitchAngle(float desiredPitchAngle);
public:
  Operation(Transmitter* transmitter, Imu* imu, /*Motion* motion, */Engine* engine,
    Surfaces* surfaces, Switch* engineSwitch, Switch* stabilizationSwitch,
    Switch* pitchStabilizationSwitch, Knob* rollStabilizationKnob,
    Knob* pitchStabilizationKnob);
  void Recalculate();
};

#endif //WING_OPERATION_H
