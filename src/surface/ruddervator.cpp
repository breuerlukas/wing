#include "ruddervator.h"

Ruddervator::Ruddervator(int servoPin) : Surface(servoPin) {

}

Ruddervator::Ruddervator(int servoPin, int trim) : Surface(servoPin, trim) {

}