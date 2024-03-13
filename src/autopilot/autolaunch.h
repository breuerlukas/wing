#ifndef WING_AUTOLAUNCH_H
#define WING_AUTOLAUNCH_H

#include "altimeter/altimeter.h"
#include "engine/engine.h"
#include "operation/operation.h"

enum AutoLaunchState {
  kAutoLaunchEngaged,
  kAutoLaunchDisengaged
};

class AutoLaunch {
private:
  Altimeter* altimeter_;
  Engine* engine_;
  Operation* operation_;
  AutoLaunchState state_ = kAutoLaunchDisengaged;
public:
  AutoLaunch(Altimeter* altimeter, Engine* engine, Operation* operation);
  void Tick();
  AutoLaunchState State();
};


#endif //WING_AUTOLAUNCH_H
