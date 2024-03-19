#ifndef WING_RUDDERVATOR_H
#define WING_RUDDERVATOR_H

#include "surface/surface.h"

class Ruddervator : public Surface {
public:
  Ruddervator(int servoPin);
  Ruddervator(int servoPin, int trim);
};


#endif //WING_RUDDERVATOR_H
