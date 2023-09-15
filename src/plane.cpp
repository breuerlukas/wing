#include "plane.h"

Plane::Plane(Transmitter* transmitter, Imu* imu, Altimeter* altimeter,
  Engine* engine, Surfaces* surfaces, Location* planeLocation,
  Operation* operation, Autopilot* autopilot, Led* led)
  : transmitter_(transmitter),
    imu_(imu),
    altimeter_(altimeter),
    engine_(engine),
    surfaces_(surfaces),
    plane_location_(planeLocation),
    operation_(operation),
    autopilot_(autopilot),
    led_(led) {

}

TinyGPSPlus gps_;
SoftwareSerial software_serial_ = SoftwareSerial(2, 3);

void Plane::Initialize() {
  engine_->Initialize();
  surfaces_->Initialize();
  delay(2000);
  led_->ChangeState(kEnabled);
  imu_->calibrate();
  altimeter_->Initialize();
  altimeter_->Calibrate();
  transmitter_->Initialize();
  software_serial_.begin(38400);
  while (gps_.satellites.value() < 4) {
    FeedGps();
  }
  led_->ChangeState(kDisabled);
  //autopilot_->Initialize();
}

void Plane::Tick() {
  transmitter_->Update();
  imu_->run();
  altimeter_->Tick();
  FeedGps();
  operation_->Recalculate();
  if (gps_.location.isUpdated()) {
    plane_location_->Update(gps_.location.lat(), gps_.location.lng());
  }
  /*autopilot_->Tick();
  if (autopilot_->State() == kDisengaged) {
    operation_->Recalculate();
  }*/
}

void Plane::FeedGps() {
  while (software_serial_.available()) {
    gps_.encode(software_serial_.read());
  }
}