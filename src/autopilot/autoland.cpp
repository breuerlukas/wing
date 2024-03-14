#include "autoland.h"

AutoLand::AutoLand(Altimeter* altimeter, Engine* engine, Operation* operation)
  : altimeter_(altimeter),
    engine_(engine),
    operation_(operation) {

}

void AutoLand::Tick() {
  if (state_ == kAutoLandDisabled) {
    return;
  }
  engine_->ApplyThrust(CalculateEngineThrust());
  operation_->AdjustPlaneOrientation(0, CalculatePitchAngle());
  CheckFlareTrigger();
}

int AutoLand::CalculateEngineThrust() {
  if (flare_) {
    return 0;
  }
  return AUTOLAND_DESCENT_THRUST;
}

float AutoLand::CalculatePitchAngle() {
  if (flare_) {
    return AUTOLAND_FLARE_ANGLE;
  }
  return -AUTOLAND_DESCENT_ANGLE;
}

void AutoLand::CheckFlareTrigger() {
  if (altimeter_->RelativeAltitude() <= AUTOLAND_FLARE_ALTITUDE) {
    flare_ = true;
  }
}

void AutoLand::Enable() {
  if (state_ == kAutoLandEnabled) {
    return;
  }
  state_ = kAutoLandEnabled;
}

void AutoLand::Disable() {
  if (state_ == kAutoLandDisabled) {
    return;
  }
  state_ = kAutoLandDisabled;
  flare_ = false;
}

AutoLandState AutoLand::State() {
  return state_;
}
