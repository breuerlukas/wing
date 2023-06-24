#ifndef WING_PLANE_H
#define WING_PLANE_H

#include "transmitter/transmitter.h"
#include "motion/motion.h"
#include "engine/engine.h"
#include "elevon/surfaces.h"
#include "operation/operation.h"

class Plane {
private:
  Transmitter* transmitter_;
  Motion* motion_;
  Engine* engine_;
  Surfaces* surfaces_;
  Operation* operation_;
public:
  Plane(Transmitter* transmitter, Motion* motion, Engine* engine,
    Surfaces* surfaces, Operation* operation);
  void Initialize();
  void Tick();
};

#endif //WING_PLANE_H
