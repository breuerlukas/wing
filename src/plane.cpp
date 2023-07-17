#include "plane.h"

Plane::Plane(Transmitter* transmitter, Motion* motion, Engine* engine,
  Surfaces* surfaces, Location* planeLocation, Operation* operation, Autopilot* autopilot)
  : transmitter_(transmitter),
    motion_(motion),
    engine_(engine),
    surfaces_(surfaces),
    plane_location(planeLocation),
    operation_(operation),
    autopilot_(autopilot) {

}


void Plane::Initialize() {
  transmitter_->Initialize();
  engine_->Initialize();
  surfaces_->Initialize();
  motion_->Initialize();
  //TODO: INITIALIZE PLANE LOCATION
  autopilot_->Initialize();
}

void Plane::Tick() {
  transmitter_->Update();
  motion_->Recalculate();
  //TODO: UPDATE PLANE LOCATION
  autopilot_->Tick();
  if (autopilot_->State() == kDisengaged) {
    operation_->Recalculate();
  }
}