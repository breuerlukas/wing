#ifndef WING_RUDDER_H
#define WING_RUDDER_H

#include "surface/surface.h"

class Rudder : public Surface {
public:
  Rudder(int servoPin);
};

#endif //WING_RUDDER_H
