#include "autoland.h"

AutoLand::AutoLand(Altimeter* altimeter, Engine* engine, Operation* operation)
  : altimeter_(altimeter),
    engine_(engine),
    operation_(operation) {

}

void AutoLand::Tick() {

}

AutoLandState AutoLand::State() {
  return state_;
}
