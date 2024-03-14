#ifndef WING_ELEVON_H
#define WING_ELEVON_H

#include "surface/surface.h"

class Elevon : public Surface {
public:
  Elevon(int servoPin);
};

#endif //WING_ELEVON_H
