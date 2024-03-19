#ifndef WING_AILERON_H
#define WING_AILERON_H

#include "surface/surface.h"

class Aileron : public Surface {
public:
  Aileron(int servoPin);
  Aileron(int servoPin, int trim);
};

#endif //WING_AILERON_H
