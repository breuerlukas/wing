#include "operation.h"

Operation::Operation(Transmitter* transmitter, Imu* imu, Altimeter* altimeter,
  Engine* engine, Surfaces* surfaces, DualSwitch* engineSwitch,
  TripleSwitch* stabilizationSwitch, Knob* rollStabilizationKnob,
  Knob* pitchStabilizationKnob, Pid* rollPidController, Pid* pitchPidController)
  : transmitter_(transmitter),
    imu_(imu),
    altimeter_(altimeter),
    engine_(engine),
    surfaces_(surfaces),
    engine_switch_(engineSwitch),
    stabilization_switch_(stabilizationSwitch),
    roll_stabilization_knob_(rollStabilizationKnob),
    pitch_stabilization_knob_(pitchStabilizationKnob),
    roll_pid_controller_(rollPidController),
    pitch_pid_controller_(pitchPidController) {

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
  int rudderStickValue = transmitter_->RudderStick()->Value();
  surfaces_->PerformAsyncRuddervatorMovement(-((float) 90 / 500) * (rudderStickValue - 1500) * 0.5);
  if (stabilization_switch_->State() == kUp) {
    surfaces_->PerformAsyncAileronMovement(((float) 90 / 500) * (aileronStickValue - 1500) * 0.5);
    surfaces_->PerformSyncRuddervatorMovement(-((float) 90 / 500) * (elevatorStickValue - 1500) * 0.5);
    surfaces_->Flush();
    return;
  }
  if (stabilization_switch_->State() == kDown) {
    AdjustPlaneOrientation(CalculateRollAngle(aileronStickValue),
      CalculatePitchAngle(elevatorStickValue));
    return;
  }
}

float Operation::CalculateRollAngle(int aileronStickValue) {
  float value = ((float) 1 / 500) * (aileronStickValue - 1500);
  return value * MAX_BANK_ANGLE;
}

float Operation::CalculatePitchAngle(int elevatorStickValue) {
  float value = ((float) 1 / 500) * (elevatorStickValue - 1500);
  if (value < 0) {
    return value * MAX_PITCH_ANGLE;
  }
  return value * MIN_PITCH_ANGLE;
}

void Operation::AdjustPlaneOrientation(float desiredRollAngle, float desiredPitchAngle) {
  AdjustPlaneRollAngle(desiredRollAngle);
  AdjustPlanePitchAngle(desiredPitchAngle);
  surfaces_->Flush();
}

void Operation::AdjustPlaneRollAngle(float desiredRollAngle) {
  float currentRollAngle = imu_->roll() - 10;
  float error = desiredRollAngle - currentRollAngle;
  error = (error < 0 ? -1 : 1) * MIN(pow(fabs(error / MAX_BANK_ANGLE), 1.2), 1) * MAX_BANK_ANGLE;
  surfaces_->PerformAsyncAileronMovement((int) (roll_pid_controller_->
    Calculate(currentRollAngle, error)));
}

void Operation::AdjustPlanePitchAngle(float desiredPitchAngle) {
  float pitchStabilizationFactor = (pitch_stabilization_knob_->Value() - 1000) / (float) 1000;
  float currentPitchAngle = -imu_->pitch() - 5;
  float error = desiredPitchAngle - currentPitchAngle;
  surfaces_->PerformSyncRuddervatorMovement(-(int) (pitch_pid_controller_->
      Calculate(currentPitchAngle, error) * 2 * pitchStabilizationFactor));
}
