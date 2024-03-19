#ifndef WING_RUDDER_H
#define WING_RUDDER_H

#include "surface/surface.h"

class Rudder : public Surface {
public:
  Rudder(int servoPin);
  Rudder(int servoPin, int trim);
};

#endif //WING_RUDDER_H
