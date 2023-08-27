#ifndef WING_PLANE_H
#define WING_PLANE_H

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include "transmitter/transmitter.h"
#include "engine/engine.h"
#include "surface/surfaces.h"
#include "operation/operation.h"
#include "autopilot/autopilot.h"

class Plane {
private:
  Transmitter* transmitter_;
  Imu* imu_;
  Engine* engine_;
  Surfaces* surfaces_;
  TinyGPSPlus* gps_;
  SoftwareSerial software_serial_ = SoftwareSerial(4, 3);
  Location* plane_location_;
  Operation* operation_;
  Autopilot* autopilot_;
public:
  Plane(Transmitter* transmitter, Imu* imu, Engine* engine,
    Surfaces* surfaces, TinyGPSPlus* gps, Location* planeLocation,
    Operation* operation, Autopilot* autopilot);
  void Initialize();
  void Tick();
};

#endif //WING_PLANE_H
