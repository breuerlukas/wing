#ifndef WING_AUTOLAND_H
#define WING_AUTOLAND_H

#include "altimeter/altimeter.h"
#include "engine/engine.h"
#include "operation/operation.h"

enum AutoLandState {
  kAutoLandEnabled,
  kAutoLandDisabled
};

class AutoLand {
private:
  Altimeter* altimeter_;
  Engine* engine_;
  Operation* operation_;
  AutoLandState state_ = kAutoLandDisabled;
  bool flare_ = false;
  int CalculateEngineThrust();
  float CalculatePitchAngle();
  void CheckFlareTrigger();
public:
  AutoLand(Altimeter* altimeter, Engine* engine, Operation* operation);
  void Tick();
  void Enable();
  void Disable();
  AutoLandState State();
};


#endif //WING_AUTOLAND_H
