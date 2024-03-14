#include "autopilot.h"

AutoPilot::AutoPilot(Transmitter* transmitter, Altimeter* altimeter,
  Engine* engine, DualSwitch* autopilotSwitch, TripleSwitch* autopilotModeSwitch,
  Location* planeLocation, Mission* mission, Operation* operation,
  AutoLaunch* autoLaunch, AutoLand* autoLand)
  : transmitter_(transmitter),
    altimeter_(altimeter),
    engine_(engine),
    autopilot_switch_(autopilotSwitch),
    autopilot_mode_switch_(autopilotModeSwitch),
    plane_location_(planeLocation),
    mission_(mission),
    operation_(operation),
    auto_launch_(autoLaunch),
    auto_land_(autoLand) {

}

void AutoPilot::Initialize() {
  mission_->Begin();
  auto_launch_->Enable();
}

void AutoPilot::Tick(double course) {
  UpdateAutopilotState();
  if (!CheckAutopilotState()) {
    auto_launch_->Disable();
    auto_land_->Disable();
    return;
  }
  auto_launch_->Tick();
  auto_land_->Tick();
  operation_->ApplyEngineThrust();
  Direction direction = plane_location_->DirectionTo(mission_->Current()->Location());
  if (CheckWaypointReaching(course, direction)) {
    return;
  }
  float rollAngle = CalculateRollAngle(direction, course);
  if (autopilot_mode_switch_->State() == kUp) {
    operation_->AdjustPlaneOrientation(rollAngle,
      operation_->CalculateDesiredPitchAngle(transmitter_->ElevatorStick()->Value()));
    return;
  }
  operation_->AdjustPlaneOrientation(rollAngle, CalculatePitchAngle());
}

bool AutoPilot::CheckAutopilotState() {
  if (is_interrupted_ && state_ == kAutoPilotEngaged) {
    state_ = kAutoPilotDisengaged;
    return false;
  }
  if (is_interrupted_ && state_ == kAutoPilotDisengaged) {
    is_interrupted_ = false;
    return false;
  }
  if (state_ == kAutoPilotDisengaged) {
    return false;
  }
  if (CheckAutopilotInterrupt()) {
    is_interrupted_ = true;
    return false;
  }
  return true;
}

bool AutoPilot::CheckAutopilotInterrupt() {
  int aileronStickValue = transmitter_->AileronStick()->Value();
  int minimalInput = (1500 - AUTOPILOT_DISCONNECT_OVERWRITE);
  int maximumInput = (1500 + AUTOPILOT_DISCONNECT_OVERWRITE);
  if (autopilot_mode_switch_->State() == kUp) {
    return (aileronStickValue < minimalInput || aileronStickValue > maximumInput);
  }
  int elevatorStickValue = transmitter_->ElevatorStick()->Value();
  return (aileronStickValue < minimalInput || aileronStickValue > maximumInput) ||
    (elevatorStickValue < minimalInput || elevatorStickValue > maximumInput);
}

void AutoPilot::UpdateAutopilotState() {
  state_ = autopilot_switch_->State() == kOn ? kAutoPilotEngaged :
    kAutoPilotDisengaged;
}

bool AutoPilot::CheckWaypointReaching(double course, Direction direction) {
  if (direction.Distance() <= DISTANCE_TO_WAYPOINT_TO_SKIP) {
    mission_->Next();
    Tick(course);
    return true;
  }
  return false;
}

float AutoPilot::CalculateRollAngle(Direction direction, double course) {
  double leftTurnAngle = -fmod((course - direction.Bearing()) + 360, 360);
  double rightTurnAngle = fmod((direction.Bearing() - course) + 360, 360);
  double rollAngleDifference = -leftTurnAngle < rightTurnAngle ? leftTurnAngle : rightTurnAngle;
  float differenceSign = rollAngleDifference < 0 ? 1 : -1;
  if (fabs(rollAngleDifference) > AUTOPILOT_MAX_BANK_ANGLE) {
    return differenceSign * (float) AUTOPILOT_MAX_BANK_ANGLE;
  }
  return differenceSign * (float) fabs(rollAngleDifference);
}

float AutoPilot::CalculatePitchAngle() {
  float currentAltitude = altimeter_->RelativeAltitude();
  float error = mission_->Current()->Altitude() - currentAltitude;
  float pitchAngle = error < 0 ? -AUTOPILOT_MAX_DESCENT_ANGLE :
    AUTOPILOT_MAX_CLIMB_ANGLE;
  if (fabs(error) <= AUTOPILOT_VERTICAL_ATTENUATION_LIMIT) {
    pitchAngle *= fabs(error / AUTOPILOT_VERTICAL_ATTENUATION_LIMIT);
  }
  return pitchAngle;
}

AutoPilotState AutoPilot::State() {
  return state_;
}