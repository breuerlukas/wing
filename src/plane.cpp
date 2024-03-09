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

void Plane::Initialize() {
  engine_->Initialize();
  engine_->ApplyThrust(1000);
  surfaces_->Initialize();
  delay(2000);
  led_->ChangeState(kEnabled);
  imu_->Initialize();
  altimeter_->Initialize();
  altimeter_->Calibrate();
  Serial3.begin(38400);
  while (gps_.satellites.value() < 1) {
    FeedGps();
  }
  transmitter_->Initialize();
  autopilot_->Initialize();
  led_->ChangeState(kDisabled);
}

void Plane::Tick() {
  transmitter_->Update();
  imu_->Tick();
  altimeter_->Tick();
  FeedGps();
  if (gps_.location.isUpdated()) {
    UpdatePlaneCourse();
    plane_location_->Update(gps_.location.lat(), gps_.location.lng());
  }
  autopilot_->Tick(plane_course_);
  if (autopilot_->State() == kDisengaged) {
    operation_->Recalculate();
  }
}

void Plane::FeedGps() {
  while (Serial3.available()) {
    gps_.encode(Serial3.read());
  }
}

void Plane::UpdatePlaneCourse() {
  if (!(plane_location_->Latitude() == gps_.location.lat() &&
        plane_location_->Longitude() == gps_.location.lng())
  ) {
    plane_course_ = gps_.courseTo(plane_location_->Latitude(),
      plane_location_->Longitude(), gps_.location.lat(), gps_.location.lng());
  }
}