#include "operation.h"

Operation::Operation(Transmitter* transmitter, Imu* imu, Engine* engine,
  Surfaces* surfaces, DualSwitch* engineSwitch, TripleSwitch* stabilizationSwitch,
  Pid* rollPidController, Pid* pitchPidController)
  : transmitter_(transmitter),
    imu_(imu),
    engine_(engine),
    surfaces_(surfaces),
    engine_switch_(engineSwitch),
    stabilization_switch_(stabilizationSwitch),
    roll_pid_controller_(rollPidController),
    pitch_pid_controller_(pitchPidController) {

}

void Operation::Recalculate() {
  ApplyEngineThrust();
  ApplySurfaceMovement();
}

void Operation::ApplyEngineThrust() {
  if (engine_switch_->State() == kOff) {
    engine_->Idle();
    return;
  }
  engine_->ApplyThrust(transmitter_->ThrottleStick()->Value());
}

void Operation::ApplySurfaceMovement() {
  ApplyRudderMovement();
  if (stabilization_switch_->State() == kUp) {
    ApplyManualSurfaceMovement();
  } else if (stabilization_switch_->State() == kMiddle) {
    ApplySemiSupportedSurfaceMovement();
  } else if (stabilization_switch_->State() == kDown) {
    ApplyFullSupportedSurfaceMovement();
  }
}

void Operation::ApplyManualSurfaceMovement() {
  int aileronStickValue = transmitter_->AileronStick()->Value();
  int elevatorStickValue = transmitter_->ElevatorStick()->Value();
  int aileronValue = ((float) 90 / 500) * (aileronStickValue - 1500) * 0.5;
  int elevatorValue = ((float) 90 / 500) * (elevatorStickValue - 1500) * 0.5;
#ifdef AILERON
  surfaces_->PerformAileronMovement(aileronValue);
#endif
#ifdef ELEVATOR
  surfaces_->PerformElevatorMovement(elevatorValue);
#endif
#ifdef ELEVON
  surfaces_->PerformAsyncElevonMovement(aileronValue);
  surfaces_->PerformSyncElevonMovement(elevatorValue);
#endif
#ifdef RUDDERVATOR
  surfaces_->PerformAsyncRuddervatorMovement(aileronValue);
  surfaces_->PerformSyncRuddervatorMovement(elevatorValue);
#endif
  surfaces_->Flush();
}

void Operation::ApplySemiSupportedSurfaceMovement() {
  int aileronStickValue = transmitter_->AileronStick()->Value();
  int elevatorStickValue = transmitter_->ElevatorStick()->Value();
  int elevatorValue = ((float) 90 / 500) * (elevatorStickValue - 1500) * 0.5;
  AdjustPlaneRollAngle(CalculateDesiredRollAngle(aileronStickValue));
#ifdef ELEVATOR
  surfaces_->PerformElevatorMovement(elevatorValue);
#endif
#ifdef ELEVON
  surfaces_->PerformSyncElevonMovement(elevatorValue);
#endif
#ifdef RUDDERVATOR
  surfaces_->PerformSyncRuddervatorMovement(elevatorValue);
#endif
  surfaces_->Flush();
}

void Operation::ApplyFullSupportedSurfaceMovement() {
  int aileronStickValue = transmitter_->AileronStick()->Value();
  int elevatorStickValue = transmitter_->ElevatorStick()->Value();
  AdjustPlaneOrientation(CalculateDesiredRollAngle(aileronStickValue),
    CalculateDesiredPitchAngle(elevatorStickValue));
}

void Operation::ApplyRudderMovement() {
  int rudderStickValue = transmitter_->RudderStick()->Value() - 1500;
  int rudderValue = ((float) 90 / 500) * rudderStickValue * 0.5;
#ifdef RUDDER
  surfaces_->PerformRudderMovement(rudderValue);
#endif
#ifdef RUDDERVATOR
  surfaces_->PerformAsyncRuddervatorMovement(rudderValue);
#endif
}

float Operation::CalculateDesiredRollAngle(int aileronStickValue) {
  float value = ((float) 1 / 500) * (aileronStickValue - 1500);
  return value * MAX_BANK_ANGLE;
}

float Operation::CalculateDesiredPitchAngle(int elevatorStickValue) {
  float value = ((float) 1 / 500) * (elevatorStickValue - 1500);
  if (value < 0) {
    return value * MAX_CLIMB_ANGLE;
  }
  return value * MAX_DESCENT_ANGLE;
}

int Operation::CalculateTrueRollAngle(float desiredRollAngle) {
  float currentRollAngle = imu_->Roll() - 5;
  float error = desiredRollAngle - currentRollAngle;
  return (int) (roll_pid_controller_->Calculate(currentRollAngle, error));
}

int Operation::CalculateTruePitchAngle(float desiredPitchAngle) {
  float currentPitchAngle = imu_->Pitch() - 5;
  float error = desiredPitchAngle - currentPitchAngle;
  return (int) (pitch_pid_controller_->Calculate(currentPitchAngle, error));
}

void Operation::AdjustPlaneOrientation(float desiredRollAngle, float desiredPitchAngle) {
  AdjustPlaneRollAngle(desiredRollAngle);
  AdjustPlanePitchAngle(desiredPitchAngle);
  surfaces_->Flush();
}

void Operation::AdjustPlaneRollAngle(float desiredRollAngle) {
  int rollAngle = CalculateTrueRollAngle(desiredRollAngle);
#ifdef AILERON
  surfaces_->PerformAileronMovement(rollAngle);
#endif
#ifdef ELEVON
  surfaces_->PerformAsyncElevonMovement(rollAngle);
#endif
#ifdef RUDDERVATOR
  surfaces_->PerformAsyncRuddervatorMovement(rollAngle);
#endif
}

void Operation::AdjustPlanePitchAngle(float desiredPitchAngle) {
  int pitchAngle = CalculateTruePitchAngle(desiredPitchAngle);
#ifdef ELEVATOR
  surfaces_->PerformElevatorMovement(pitchAngle);
#endif
#ifdef ELEVON
  surfaces_->PerformSyncElevonMovement(pitchAngle);
#endif
#ifdef RUDDERVATOR
  surfaces_->PerformSyncRuddervatorMovement(pitchAngle);
#endif
}
