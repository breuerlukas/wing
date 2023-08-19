#include "operation.h"

Operation::Operation(Transmitter* transmitter, Imu* imu, /*Motion* motion, */Engine* engine,
  Surfaces* surfaces, Switch* engineSwitch, Switch* stabilizationSwitch,
  Switch* pitchStabilizationSwitch, Knob* rollStabilizationKnob,
  Knob* pitchStabilizationKnob)
  : transmitter_(transmitter),
    //motion_(motion),
    imu_(imu),
    engine_(engine),
    surfaces_(surfaces),
    engine_switch_(engineSwitch),
    stabilization_switch_(stabilizationSwitch),
    pitch_stabilization_switch_(pitchStabilizationSwitch),
    roll_stabilization_knob_(rollStabilizationKnob),
    pitch_stabilization_knob_(pitchStabilizationKnob) {
  time = millis();
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
  float rollStabilizationFactor = (roll_stabilization_knob_->Value() - 1000) / (float) 1000;
  float pitchStabilizationFactor = (pitch_stabilization_knob_->Value() - 1000) / (float) 1000;
  if (stabilization_switch_->State() == kOff) {
    surfaces_->PerformAsyncAileronMovement(((float) 90 / 500) *
      (aileronStickValue - 1500) * rollStabilizationFactor);
    surfaces_->PerformSyncRuddervatorMovement(-((float) 90 / 500) *
      (elevatorStickValue - 1500) * pitchStabilizationFactor);
    surfaces_->PerformAsyncRuddervatorMovement(-((float) 90 / 500) *
      (rudderStickValue - 1500));
    surfaces_->Flush();
    return;
  }
  AdjustPlaneRollAngle(CalculateRollAngle(aileronStickValue));
  surfaces_->PerformSyncRuddervatorMovement(-((float) 90 / 500) *
    (elevatorStickValue - 1500) * pitchStabilizationFactor);
  surfaces_->PerformAsyncRuddervatorMovement(-((float) 90 / 500) *
    (rudderStickValue - 1500));
  surfaces_->Flush();
}

float Operation::CalculateRollAngle(int aileronStickValue) {
  float value = ((float) 1 / 500) * (aileronStickValue - 1500);
  float transformed = (value < 0 ? - 1 : 1) * pow(fabs(value), 0.5);
  return transformed * MAX_BANK_ANGLE;
}

/*float Operation::CalculatePitchAngle(int elevatorStickValue) {
  float value = ((float) 1 / 500) * (elevatorStickValue - 1500);
  float transformed = (value < 0 ? - 1 : 1) * pow(fabs(value), 0.5);
  if (transformed < 0) {
    return transformed * MAX_PITCH_ANGLE;
  }
  return transformed * MIN_PITCH_ANGLE;
}

void Operation::AdjustPlaneOrientation(float desiredRollAngle, float desiredPitchAngle) {
  AdjustPlaneRollAngle(desiredRollAngle);
  AdjustPlanePitchAngle(desiredPitchAngle);
  surfaces_->Flush();
}*/

void Operation::AdjustPlaneRollAngle(float desiredRollAngle) {
  timePrev = time;  // the previous time is stored before the actual time read
  time = millis();  // actual time read
  elapsedTime = (time - timePrev) / 1000;
  float rollStabilizationFactor = (roll_stabilization_knob_->Value() - 1000) / (float) 1000;
  //float currentRollAngle = motion_->Roll();
  float currentRollAngle = imu_->roll();
  float rollDifference = desiredRollAngle - currentRollAngle;
  //pid_p = (rollDifference < 0 ? -1 : 1) * MIN(pow(fabs((rollDifference * kp) / MAX_BANK_ANGLE), 1.5), 1.2) * MAX_BANK_ANGLE * 2;
  pid_p = rollDifference * kp;
  /*if(-5 < rollDifference < 5) {
    pid_i = pid_i + (ki * rollDifference);
  }*/
  pid_d = kd * (((rollDifference - previous_error) - fabs(desiredRollAngle - previous_desired_roll)) / elapsedTime);
  PID = pid_p + pid_i + pid_d;
  //Serial.println(PID);
  surfaces_->PerformAsyncAileronMovement((int) (PID * 2 * rollStabilizationFactor));
  previous_error = rollDifference;
  previous_desired_roll = desiredRollAngle;
}

/*void Operation::AdjustPlanePitchAngle(float desiredPitchAngle) {
  float pitchStabilizationFactor = (pitch_stabilization_knob_->Value() - 1000) / (float) 1000;
  //float currentPitchAngle = motion_->Pitch();
    float currentPitchAngle = imu_->pitch();
  float pitchDifference = desiredPitchAngle - currentPitchAngle;
  surfaces_->PerformSyncMovement(-(int) (pitchDifference * pitchStabilizationFactor));
}*/
