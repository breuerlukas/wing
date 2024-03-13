#ifndef WING_AUTOLAND_H
#define WING_AUTOLAND_H

#include "altimeter/altimeter.h"
#include "engine/engine.h"
#include "operation/operation.h"

enum AutoLandState {
  kAutoLandEngaged,
  kAutoLandDisengaged
};

class AutoLand {
private:
  Altimeter* altimeter_;
  Engine* engine_;
  Operation* operation_;
  AutoLandState state_ = kAutoLandDisengaged;
public:
  AutoLand(Altimeter* altimeter, Engine* engine, Operation* operation);
  void Tick();
  AutoLandState State();
};


#endif //WING_AUTOLAND_H
