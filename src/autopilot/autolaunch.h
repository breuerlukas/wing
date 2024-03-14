#ifndef WING_AUTOLAUNCH_H
#define WING_AUTOLAUNCH_H

#include "altimeter/altimeter.h"
#include "engine/engine.h"
#include "operation/operation.h"

enum AutoLaunchState {
  kAutoLaunchEnabled,
  kAutoLaunchDisabled
};

class AutoLaunch {
private:
  Imu* imu_;
  Altimeter* altimeter_;
  Engine* engine_;
  Operation* operation_;
  AutoLaunchState state_ = kAutoLaunchDisabled;
  bool engine_trigger_ = false;
  void CheckEngineTrigger();
  int CalculateEngineThrust();
  void CheckTargetAltitudeReaching();
public:
  AutoLaunch(Imu* imu, Altimeter* altimeter, Engine* engine, Operation* operation);
  void Tick();
  void Enable();
  void Disable();
  AutoLaunchState State();
};


#endif //WING_AUTOLAUNCH_H
