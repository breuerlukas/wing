#include "autopilot.h"

Autopilot::Autopilot(Transmitter* transmitter, Motion* motion, Engine* engine,
  Surfaces* surfaces, Switch* autopilotSwitch, Knob* rollStabilizationKnob,
  Knob* pitchStabilizationKnob, TinyGPSPlus* gps, Location* planeLocation, Mission* mission)
  : transmitter_(transmitter),
    motion_(motion),
    engine_(engine),
    surfaces_(surfaces),
    autopilot_switch_(autopilotSwitch),
    roll_stabilization_knob_(rollStabilizationKnob),
    pitch_stabilization_knob_(pitchStabilizationKnob),
    gps_(gps),
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
  Direction direction = plane_location_->DirectionTo(mission_->Current().Location());
  if (direction.Distance() <= DISTANCE_TO_WAYPOINT_TO_SKIP) {
    mission_->Next();
    Tick();
    return;
  }
  double currentCourse = gps_->course.deg();
  double leftTurnAngle = -fmod((currentCourse - direction.Bearing()) + 360, 360);
  double rightTurnAngle = fmod((direction.Bearing() - currentCourse) + 360, 360);
  double rollAngleDifference = -leftTurnAngle < rightTurnAngle ? leftTurnAngle : rightTurnAngle;
  //TODO: CALCULATE PITCH ANGLE (PROBABLY VIA BAROMETER)
  AdjustPlaneOrientation(CalculateRollAngle(rollAngleDifference), 0);
}

void Autopilot::UpdateAutopilotState() {
  state_ = autopilot_switch_->State() == kOn ? kEngaged : kDisengaged;
}

float Autopilot::CalculateRollAngle(double rollAngleDifference) {
  float value = rollAngleDifference / 180;
  float transformed = (value < 0 ? - 1 : 1) * pow(fabs(value), 1.8);
  return transformed * MAX_BANK_ANGLE;
}

float Autopilot::CalculatePitchAngle(double pitchAngleDifference) {
  return 0;
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