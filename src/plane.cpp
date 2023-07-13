#include "plane.h"

Plane::Plane(Transmitter* transmitter, Motion* motion, Engine* engine,
  Surfaces* surfaces, Operation* operation, Autopilot* autopilot)
  : transmitter_(transmitter),
    motion_(motion),
    engine_(engine),
    surfaces_(surfaces),
    operation_(operation),
    autopilot_(autopilot) {

}


void Plane::Initialize() {
  transmitter_->Initialize();
  engine_->Initialize();
  surfaces_->Initialize();
  motion_->Initialize();
  autopilot_->Initialize();
}

void Plane::Tick() {
  transmitter_->Update();
  motion_->Recalculate();
  if (autopilot_->State() == kDisengaged) {
    operation_->Recalculate();
    return;
  }
  autopilot_->Tick();
}