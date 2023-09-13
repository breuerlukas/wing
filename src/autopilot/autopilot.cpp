#include "autopilot.h"

Autopilot::Autopilot(Transmitter* transmitter, Imu* imu, Altimeter* altimeter,
  Engine* engine, Surfaces* surfaces, DualSwitch* engineSwitch,
  DualSwitch* autopilotSwitch, TripleSwitch* autopilotModeSwitch,
  Pid* rollPidController, Pid* pitchPidController, TinyGPSPlus* gps,
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
    gps_(gps),
    plane_location_(planeLocation),
    mission_(mission) {

}

void Autopilot::Initialize() {

}

void Autopilot::Tick() {
  if (CheckAutopilotInterrupt()) {
    state_ = kDisengaged;
    return;
  }
  UpdateAutopilotState();
  if (state_ == kDisengaged) {
    return;
  }
  ApplyEngineThrust();
  Direction direction = plane_location_->DirectionTo(mission_->Current().Location());
  if (direction.Distance() <= DISTANCE_TO_WAYPOINT_TO_SKIP) {
    mission_->Next();
    Tick();
    return;
  }
  if (autopilot_mode_switch_->State() == kUp) {
    AdjustPlaneOrientation(CalculateRollAngle(direction),
      CalculatePitchAngleManual());
    return;
  }
  AdjustPlaneOrientation(CalculateRollAngle(direction),
    CalculatePitchAngleAltitude());
}

bool Autopilot::CheckAutopilotInterrupt() {
  int aileronStickValue = transmitter_->AileronStick()->Value();
  int elevatorStickValue = transmitter_->ElevatorStick()->Value();
  return (aileronStickValue < 1400 || aileronStickValue > 1500) ||
    (elevatorStickValue < 1400 || elevatorStickValue > 1500);
}

void Autopilot::UpdateAutopilotState() {
  state_ = autopilot_switch_->State() == kOn ? kEngaged : kDisengaged;
}

void Autopilot::ApplyEngineThrust() {
  if (engine_switch_->State() == kOff) {
    engine_->ApplyThrust(1000);
    return;
  }
  engine_->ApplyThrust(transmitter_->ThrottleStick()->Value());
}

float Autopilot::CalculateRollAngle(Direction direction) {
  double currentCourse = gps_->course.deg();
  double leftTurnAngle = -fmod((currentCourse - direction.Bearing()) + 360, 360);
  double rightTurnAngle = fmod((direction.Bearing() - currentCourse) + 360, 360);
  double rollAngleDifference = -leftTurnAngle < rightTurnAngle ? leftTurnAngle : rightTurnAngle;
  if (fabs(rollAngleDifference) > 30) {
    return (rollAngleDifference < 0 ? -1 : 1) * (float) AUTOPILOT_MAX_BANK_ANGLE;
  }
  return (rollAngleDifference < 0 ? -1 : 1) * (float) AUTOPILOT_MAX_BANK_ANGLE *
    pow(fabs(rollAngleDifference / 30), 1.2);
}

float Autopilot::CalculatePitchAngleManual() {
  float value = ((float) 1 / 500) * (transmitter_->ElevatorStick()->Value() - 1500);
  if (value < 0) {
    return value * MAX_PITCH_ANGLE;
  }
  return value * MIN_PITCH_ANGLE;
}

float Autopilot::CalculatePitchAngleAltitude() {
  float currentAltitude = altimeter_->RelativeAltitude();
  float error = (mission_->Current().Altitude() - currentAltitude) * 5;
  float pitchAngle;
  if (fabs(error) > 10) {
    pitchAngle = (error < 0 ? -MIN_PITCH_ANGLE : MAX_PITCH_ANGLE) * ((float) 2 / 3);
  } else {
    pitchAngle = (error < 0 ? -MIN_PITCH_ANGLE : MAX_PITCH_ANGLE) *
      ((float) 2 / 3) * pow(fabs(error / 10), 1.2);
  }
  return pitchAngle;
}

void Autopilot::AdjustPlaneOrientation(float desiredRollAngle, float desiredPitchAngle) {
  AdjustPlaneRollAngle(desiredRollAngle);
  AdjustPlanePitchAngle(desiredPitchAngle);
  surfaces_->Flush();
}

void Autopilot::AdjustPlaneRollAngle(float desiredRollAngle) {
  float currentRollAngle = imu_->roll() - 10;
  float error = desiredRollAngle - currentRollAngle;
  error = (error < 0 ? -1 : 1) * MIN(pow(fabs(error / MAX_BANK_ANGLE), 1.2), 1) * MAX_BANK_ANGLE;
  surfaces_->PerformAsyncAileronMovement((int) (roll_pid_controller_->
    Calculate(currentRollAngle, error)));
}

void Autopilot::AdjustPlanePitchAngle(float desiredPitchAngle) {
  float currentPitchAngle = imu_->pitch() + 5;
  float error = desiredPitchAngle - currentPitchAngle;
  surfaces_->PerformSyncRuddervatorMovement(-(int) (pitch_pid_controller_->
    Calculate(currentPitchAngle, error)));
}

AutopilotState Autopilot::State() {
  return state_;
}