#include "rudder.h"

Rudder::Rudder(int servoPin) : Surface(servoPin) {

}

Rudder::Rudder(int servoPin, int trim) : Surface(servoPin, trim) {

}