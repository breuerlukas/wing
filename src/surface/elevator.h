#ifndef WING_ELEVATOR_H
#define WING_ELEVATOR_H

#include "surface/surface.h"

class Elevator : public Surface {
public:
  Elevator(int servoPin);
};

#endif //WING_ELEVATOR_H
