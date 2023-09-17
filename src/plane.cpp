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
AltSoftSerial software_serial_;

void Plane::Initialize() {
  engine_->Initialize();
  engine_->ApplyThrust(1000);
  surfaces_->Initialize();
  delay(2000);
  led_->ChangeState(kEnabled);
  imu_->calibrate();
  altimeter_->Initialize();
  altimeter_->Calibrate();
  software_serial_.begin(38400);
  while (gps_.satellites.value() < 1) {
    FeedGps();
  }
  led_->ChangeState(kDisabled);
  transmitter_->Initialize();
  autopilot_->Initialize();
}

void Plane::Tick() {
  transmitter_->Update();
  imu_->run();
  altimeter_->Tick();
  FeedGps();
  if (gps_.location.isUpdated()) {
    plane_course_ = gps_.courseTo(plane_location_->Latitude(),
      plane_location_->Longitude(), gps_.location.lat(), gps_.location.lng());
    plane_location_->Update(gps_.location.lat(), gps_.location.lng());
  }
  autopilot_->Tick(plane_course_);
  if (autopilot_->State() == kDisengaged) {
    operation_->Recalculate();
  }
}

void Plane::FeedGps() {
  while (software_serial_.available()) {
    gps_.encode(software_serial_.read());
  }
}