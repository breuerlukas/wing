#include "autopilot.h"

Autopilot::Autopilot(Transmitter* transmitter, Imu* imu, Engine* engine,
  Surfaces* surfaces, DualSwitch* autopilotSwitch, TinyGPSPlus* gps,
  Location* planeLocation, Mission* mission)
  : transmitter_(transmitter),
    imu_(imu),
    engine_(engine),
    surfaces_(surfaces),
    autopilot_switch_(autopilotSwitch),
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
  /*if (stabilization_switch_->State() == kDown) {
  long time = millis();
  float desiredVerticalSpeed = ((float) 1 / 500) *
    (elevatorStickValue - 1500) * (float) ALTITUDE_CHANGE_RATE;
  float currentAltitude = altimeter_->RelativeAltitude();
  if ((fabs(desiredVerticalSpeed) >= 0.95 * (float) ALTITUDE_CHANGE_RATE) &&
      ((desired_altitude_ > currentAltitude && desiredVerticalSpeed < 0) ||
      (desired_altitude_ < currentAltitude && desiredVerticalSpeed > 0))
    ) {
    desired_altitude_ = currentAltitude;
    last_altitude_reset = time;
  }
  if (last_altitude_reset + 500 < time) {
    desired_altitude_ += desiredVerticalSpeed;
  }
  float error = (desired_altitude_ - currentAltitude) * 5;
  float pitchAngle;
  if (fabs(error) > 10) {
    pitchAngle = (error < 0 ? -MIN_PITCH_ANGLE : MAX_PITCH_ANGLE) * ((float) 2 / 3);
  } else {
    pitchAngle = (error < 0 ? -MIN_PITCH_ANGLE : MAX_PITCH_ANGLE) * ((float) 2 / 3) * pow(fabs(error / 10), 1.2);
  }
  AdjustPlaneOrientation(CalculateRollAngle(aileronStickValue), pitchAngle);
  return;
}*/
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
  float currentRollAngle = imu_->roll();
  float currentPitchAngle = imu_->pitch();
  float rollDifference = desiredRollAngle - currentRollAngle;
  float pitchDifference = desiredPitchAngle - currentPitchAngle;
  //surfaces_->PerformAsyncMovement((int) (rollDifference * rollStabilizationFactor));
  //surfaces_->PerformSyncMovement(-(int) (pitchDifference * pitchStabilizationFactor));
  surfaces_->Flush();
}

AutopilotState Autopilot::State() {
  return state_;
}