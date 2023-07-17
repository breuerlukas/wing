#include "operation.h"

Operation::Operation(Transmitter* transmitter, Motion* motion, Engine* engine,
  Surfaces* surfaces, Switch* engineSwitch, Switch* stabilizationSwitch,
  Knob* rollStabilizationKnob, Knob* pitchStabilizationKnob)
  : transmitter_(transmitter),
    motion_(motion),
    engine_(engine),
    surfaces_(surfaces),
    engine_switch_(engineSwitch),
    stabilization_switch_(stabilizationSwitch),
    roll_stabilization_knob_(rollStabilizationKnob),
    pitch_stabilization_knob_(pitchStabilizationKnob) {

}

void Operation::Recalculate() {
  ApplyEngineThrust();
  ApplySurfaceMovement();
}

void Operation::ApplyEngineThrust() {
  if (engine_switch_->State() == kOff) {
    engine_->ApplyThrust(1000);
    return;
  }
  engine_->ApplyThrust(transmitter_->ThrottleStick()->Value());
}

void Operation::ApplySurfaceMovement() {
  int aileronStickValue = transmitter_->AileronStick()->Value();
  int elevatorStickValue = transmitter_->ElevatorStick()->Value();
  if (stabilization_switch_->State() == kOff) {
    float rollStabilizationFactor = (roll_stabilization_knob_->Value() - 1000) / (float) 1000;
    float pitchStabilizationFactor = (pitch_stabilization_knob_->Value() - 1000) / (float) 1000;
    surfaces_->PerformAsyncMovement(((float) 90 / 500) * (aileronStickValue - 1500) * rollStabilizationFactor);
    surfaces_->PerformSyncMovement(-((float) 90 / 500) * (elevatorStickValue - 1500) * pitchStabilizationFactor);
    surfaces_->Flush();
    return;
  }
  AdjustPlaneOrientation(CalculateRollAngle(aileronStickValue), CalculatePitchAngle(elevatorStickValue));
}

void Operation::AdjustPlaneOrientation(float desiredRollAngle, float desiredPitchAngle) {
  float rollStabilizationFactor = (roll_stabilization_knob_->Value() - 1000) / (float) 1000;
  float pitchStabilizationFactor = (pitch_stabilization_knob_->Value() - 1000) / (float) 1000;
  float currentRollAngle = motion_->Roll();
  float currentPitchAngle = motion_->Pitch();
  float rollDifference = desiredRollAngle - currentRollAngle;
  float pitchDifference = desiredPitchAngle - currentPitchAngle;
  surfaces_->PerformAsyncMovement((int) (rollDifference * rollStabilizationFactor));
  surfaces_->PerformSyncMovement(-(int) (pitchDifference * pitchStabilizationFactor));
  surfaces_->Flush();
}

float Operation::CalculateRollAngle(int aileronStickValue) {
  float value = ((float) 1 / 500) * (aileronStickValue - 1500);
  float transformed = (value < 0 ? - 1 : 1) * pow(fabs(value), 0.5);
  return transformed * MAX_BANK_ANGLE;
}

float Operation::CalculatePitchAngle(int elevatorStickValue) {
  float value = ((float) 1 / 500) * (elevatorStickValue - 1500);
  float transformed = (value < 0 ? - 1 : 1) * pow(fabs(value), 0.5);
  if (transformed < 0) {
    return transformed * MIN_PITCH_ANGLE;
  }
  return transformed * MAX_PITCH_ANGLE;
}
