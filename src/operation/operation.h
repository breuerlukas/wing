#ifndef WING_OPERATION_H
#define WING_OPERATION_H

#include <cmath>
#include "transmitter/transmitter.h"
#include "motion/motion.h"
#include "engine/engine.h"
#include "elevon/surfaces.h"
#include "transmitter/channel/switch.h"
#include "transmitter/channel/knob.h"

#define MAX_BANK_ANGLE 60
#define MAX_PITCH_ANGLE 45
#define MIN_PITCH_ANGLE 45

class Operation {
private:
  Transmitter* transmitter_;
  Motion* motion_;
  Engine* engine_;
  Surfaces* surfaces_;
  Switch* engine_switch_;
  Switch* stabilization_switch_;
  Knob* roll_stabilization_knob_;
  Knob* pitch_stabilization_knob_;
  void ApplyEngineThrust();
  void ApplySurfaceMovement();
  float CalculateRollAngle(int aileronStickValue);
  float CalculatePitchAngle(int elevatorStickValue);
public:
  Operation(Transmitter* transmitter, Motion* motion, Engine* engine,
    Surfaces* surfaces, Switch* engineSwitch,  Switch* stabilizationSwitch,
    Knob* rollStabilizationKnob, Knob* pitchStabilizationKnob);
  void Recalculate();
};

#endif //WING_OPERATION_H
