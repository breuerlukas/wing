#include "plane.h"

Plane::Plane(Transmitter* transmitter, Imu* imu, Altimeter* altimeter,
  Engine* engine, Surfaces* surfaces, TinyGPSPlus* gps, Location* planeLocation,
  Operation* operation, Autopilot* autopilot)
  : transmitter_(transmitter),
    imu_(imu),
    altimeter_(altimeter),
    engine_(engine),
    surfaces_(surfaces),
    gps_(gps),
    plane_location_(planeLocation),
    operation_(operation),
    autopilot_(autopilot) {

}

void Plane::Initialize() {
  delay(2000);
  imu_->calibrate();
  //altimeter_->Initialize();
  //altimeter_->Calibrate();
  transmitter_->Initialize();
  engine_->Initialize();
  surfaces_->Initialize();
  //software_serial_.begin(38400);
  //autopilot_->Initialize();
}

void Plane::Tick() {
  transmitter_->Update();
  imu_->run();
  //altimeter_->Tick();
  operation_->Recalculate();
  /*while (software_serial_.available() > 0) {
    gps_->encode(software_serial_.read());
  }
  if (gps_->location.isUpdated()) {
    plane_location_->Update(gps_->location.lat(), gps_->location.lng());
  }*/
  /*autopilot_->Tick();
  if (autopilot_->State() == kDisengaged) {
    operation_->Recalculate();
  }*/
}