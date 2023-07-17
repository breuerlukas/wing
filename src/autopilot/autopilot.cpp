#include "autopilot.h"

Autopilot::Autopilot(Transmitter* transmitter, Motion* motion, Engine* engine,
  Surfaces* surfaces, Switch* autopilotSwitch, Knob* rollStabilizationKnob,
  Knob* pitchStabilizationKnob, Location* planeLocation, Mission* mission)
  : transmitter_(transmitter),
    motion_(motion),
    engine_(engine),
    surfaces_(surfaces),
    autopilot_switch_(autopilotSwitch),
    roll_stabilization_knob_(rollStabilizationKnob),
    pitch_stabilization_knob_(pitchStabilizationKnob),
    plane_location_(planeLocation),
    mission_(mission) {

}

void Autopilot::Initialize() {

}

void Autopilot::Tick() {
  UpdateAutopilotState();
  if (state_ == kDisengaged) {
    return;
  }

}

void Autopilot::UpdateAutopilotState() {
  state_ = autopilot_switch_->State() == kOn ? kEngaged : kDisengaged;
}

void Autopilot::AdjustPlaneOrientation(float desiredRollAngle, float desiredPitchAngle) {
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

AutopilotState Autopilot::State() {
  return state_;
}