#include "autolaunch.h"

AutoLaunch::AutoLaunch(Altimeter* altimeter, Engine* engine, Operation* operation)
  : altimeter_(altimeter),
    engine_(engine),
    operation_(operation) {

}

void AutoLaunch::Tick() {

}

AutoLaunchState AutoLaunch::State() {
  return state_;
}
