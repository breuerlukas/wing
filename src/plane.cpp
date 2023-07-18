#include "plane.h"

Plane::Plane(Transmitter* transmitter, Motion* motion, Engine* engine,
  Surfaces* surfaces, Location* planeLocation, Operation* operation, Autopilot* autopilot)
  : transmitter_(transmitter),
    motion_(motion),
    engine_(engine),
    surfaces_(surfaces),
    plane_location_(planeLocation),
    operation_(operation),
    autopilot_(autopilot) {

}

void Plane::Initialize() {
  transmitter_->Initialize();
  engine_->Initialize();
  surfaces_->Initialize();
  motion_->Initialize();
  software_serial_.begin(38400);
  autopilot_->Initialize();
}

void Plane::Tick() {
  transmitter_->Update();
  motion_->Recalculate();
  while (software_serial_.available() > 0) {
    gps_.encode(software_serial_.read());
  }
  if (gps_.location.isUpdated()) {
    plane_location_->Update(gps_.location.lat(), gps_.location.lng());
  }
  autopilot_->Tick();
  if (autopilot_->State() == kDisengaged) {
    operation_->Recalculate();
  }
}