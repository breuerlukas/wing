#include "autolaunch.h"

AutoLaunch::AutoLaunch(Imu* imu, Altimeter* altimeter, Engine* engine,
  Operation* operation)
  : imu_(imu),
    altimeter_(altimeter),
    engine_(engine),
    operation_(operation) {

}

void AutoLaunch::Tick() {
  if (state_ == kAutoLaunchDisabled) {
    return;
  }
  if (!engine_trigger_) {
    CheckEngineTrigger();
  }
  engine_->ApplyThrust(CalculateEngineThrust());
  operation_->AdjustPlaneOrientation(0, AUTOLAUNCH_CLIMB_ANGLE);
  CheckTargetAltitudeReaching();
}

void AutoLaunch::CheckEngineTrigger() {
  if (imu_->Acceleration() >= AUTOLAUNCH_ENGINE_TRIGGER_ACCELERATION * 10000) {
    engine_trigger_ = true;
  }
}

int AutoLaunch::CalculateEngineThrust() {
  if (!engine_trigger_) {
    return 0;
  }
  return AUTOLAUNCH_THRUST;
}

void AutoLaunch::CheckTargetAltitudeReaching() {
  if (altimeter_->RelativeAltitude() >= AUTOLAUNCH_TARGET_ALTITUDE) {
    state_ = kAutoLaunchDisabled;
  }
}

void AutoLaunch::Enable() {
  if (state_ == kAutoLaunchEnabled) {
    return;
  }
  state_ = kAutoLaunchEnabled;
}

void AutoLaunch::Disable() {
  if (state_ == kAutoLaunchDisabled) {
    return;
  }
  state_ = kAutoLaunchDisabled;
  engine_trigger_ = false;
}

AutoLaunchState AutoLaunch::State() {
  return state_;
}
