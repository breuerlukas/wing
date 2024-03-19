#include "elevator.h"

Elevator::Elevator(int servoPin) : Surface(servoPin) {

}

Elevator::Elevator(int servoPin, int trim) : Surface(servoPin, trim) {

}