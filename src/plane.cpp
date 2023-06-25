#include "plane.h"

Plane::Plane(Transmitter* transmitter, Motion* motion, Engine* engine,
  Surfaces* surfaces, Operation* operation)
  : transmitter_(transmitter),
    motion_(motion),
    engine_(engine),
    surfaces_(surfaces),
    operation_(operation) {

}


void Plane::Initialize() {
  transmitter_->Initialize();
  engine_->Initialize();
  surfaces_->Initialize();
  motion_->Initialize();
}

void Plane::Tick() {
  transmitter_->Update();
  motion_->Recalculate();
  operation_->Recalculate();
}