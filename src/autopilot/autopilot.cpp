#include "autopilot.h"

Autopilot::Autopilot(Transmitter* transmitter, Imu* imu, Altimeter* altimeter,
  Engine* engine, Surfaces* surfaces, DualSwitch* engineSwitch,
  DualSwitch* autopilotSwitch, TripleSwitch* autopilotModeSwitch,
  Pid* rollPidController, Pid* pitchPidController,
  Location* planeLocation, Mission* mission)
  : transmitter_(transmitter),
    imu_(imu),
    altimeter_(altimeter),
    engine_(engine),
    surfaces_(surfaces),
    engine_switch_(engineSwitch),
    autopilot_switch_(autopilotSwitch),
    autopilot_mode_switch_(autopilotModeSwitch),
    roll_pid_controller_(rollPidController),
    pitch_pid_controller_(pitchPidController),
    plane_location_(planeLocation),
    mission_(mission) {

}

void Autopilot::Initialize() {
  mission_->Begin();
}

void Autopilot::Tick(double course) {
  UpdateAutopilotState();
  if (!CheckAutopilotState()) {
    return;
  }
  ApplyEngineThrust();
  Direction direction = plane_location_->DirectionTo(mission_->Current()->Location());
  if (CheckWaypointReaching(course, direction)) {
    return;
  }
  float rollAngle = CalculateRollAngle(direction, course);
  if (autopilot_mode_switch_->State() == kUp) {
    AdjustPlaneOrientation(rollAngle, CalculatePitchAngleManual());
    return;
  }
  AdjustPlaneOrientation(rollAngle, CalculatePitchAngleAltitude());
}

bool Autopilot::CheckAutopilotState() {
  if (is_interrupted_ && state_ == kEngaged) {
    state_ = kDisengaged;
    return false;
  }
  if (is_interrupted_ && state_ == kDisengaged) {
    is_interrupted_ = false;
    return false;
  }
  if (state_ == kDisengaged) {
    return false;
  }
  if (CheckAutopilotInterrupt()) {
    is_interrupted_ = true;
    return false;
  }
  return true;
}

bool Autopilot::CheckAutopilotInterrupt() {
  int aileronStickValue = transmitter_->AileronStick()->Value();
  if (autopilot_mode_switch_->State() == kUp) {
    return (aileronStickValue < 1200 || aileronStickValue > 1800);
  }
  int elevatorStickValue = transmitter_->ElevatorStick()->Value();
  return (aileronStickValue < 1200 || aileronStickValue > 1800) ||
    (elevatorStickValue < 1200 || elevatorStickValue > 1800);
}

void Autopilot::UpdateAutopilotState() {
  state_ = autopilot_switch_->State() == kOn ? kEngaged : kDisengaged;
}

bool Autopilot::CheckWaypointReaching(double course, Direction direction) {
  if (direction.Distance() <= DISTANCE_TO_WAYPOINT_TO_SKIP) {
    mission_->Next();
    Tick(course);
    return true;
  }
  return false;
}

void Autopilot::ApplyEngineThrust() {
  if (engine_switch_->State() == kOff) {
    engine_->ApplyThrust(1000);
    return;
  }
  engine_->ApplyThrust(transmitter_->ThrottleStick()->Value());
}

float Autopilot::CalculateRollAngle(Direction direction, double course) {
  double leftTurnAngle = -fmod((course - direction.Bearing()) + 360, 360);
  double rightTurnAngle = fmod((direction.Bearing() - course) + 360, 360);
  double rollAngleDifference = -leftTurnAngle < rightTurnAngle ? leftTurnAngle : rightTurnAngle;
  if (fabs(rollAngleDifference) > 45) {
    return (rollAngleDifference < 0 ? 1 : -1) * (float) AUTOPILOT_MAX_BANK_ANGLE;
  }
  return (rollAngleDifference < 0 ? 1 : -1) * (float) AUTOPILOT_MAX_BANK_ANGLE *
    pow(fabs(rollAngleDifference / 45), 1.2);
}

float Autopilot::CalculatePitchAngleManual() {
  float value = ((float) 1 / 500) * ((float) transmitter_->ElevatorStick()->Value() - 1500);
  if (value > 0) {
    return value * MAX_CLIMB_ANGLE;
  }
  return value * MAX_DESCENT_ANGLE;
}

float Autopilot::CalculatePitchAngleAltitude() {
  float currentAltitude = altimeter_->RelativeAltitude();
  float error = mission_->Current()->Altitude() - currentAltitude;
  float pitchAngle = error < 0 ? -AUTOPILOT_MAX_DESCENT_ANGLE :
    AUTOPILOT_MAX_CLIMB_ANGLE;
  if (fabs(error) <= 10) {
    pitchAngle *= pow(fabs(error / 10), 1.2);
  }
  return pitchAngle;
}

void Autopilot::AdjustPlaneOrientation(float desiredRollAngle, float desiredPitchAngle) {
  AdjustPlaneRollAngle(desiredRollAngle);
  AdjustPlanePitchAngle(desiredPitchAngle);
  surfaces_->Flush();
}

void Autopilot::AdjustPlaneRollAngle(float desiredRollAngle) {
  float currentRollAngle = imu_->Roll();
  float error = desiredRollAngle - currentRollAngle;
  surfaces_->PerformAsyncAileronMovement((int) (roll_pid_controller_->
      Calculate(currentRollAngle, error)) + 5);
}

void Autopilot::AdjustPlanePitchAngle(float desiredPitchAngle) {
  float currentPitchAngle = -imu_->Pitch() - 5;
  float error = desiredPitchAngle - currentPitchAngle;
  surfaces_->PerformSyncRuddervatorMovement(-(int) (pitch_pid_controller_->
    Calculate(currentPitchAngle, error)));
}

AutopilotState Autopilot::State() {
  return state_;
}