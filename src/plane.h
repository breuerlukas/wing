#ifndef WING_PLANE_H
#define WING_PLANE_H

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include "transmitter/transmitter.h"
#include "imu/imu.h"
#include "altimeter/altimeter.h"
#include "engine/engine.h"
#include "surface/surfaces.h"
#include "operation/operation.h"
#include "autopilot/autopilot.h"
#include "led/led.h"

class Plane {
private:
  Transmitter* transmitter_;
  Imu* imu_;
  Altimeter* altimeter_;
  Engine* engine_;
  Surfaces* surfaces_;
  Location* plane_location_;
  Operation* operation_;
  Autopilot* autopilot_;
  Led* led_;
  void FeedGps();
public:
  Plane(Transmitter* transmitter, Imu* imu, Altimeter* altimeter, Engine* engine,
    Surfaces* surfaces, Location* planeLocation,
    Operation* operation, Autopilot* autopilot, Led* led);
  void Initialize();
  void Tick();
};

#endif //WING_PLANE_H
