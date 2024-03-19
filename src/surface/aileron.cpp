#include "aileron.h"

Aileron::Aileron(int servoPin) : Surface(servoPin) {

}

Aileron::Aileron(int servoPin, int trim) : Surface(servoPin, trim) {

}