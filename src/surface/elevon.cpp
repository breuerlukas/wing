#include "elevon.h"

Elevon::Elevon(int servoPin) : Surface(servoPin) {

}

Elevon::Elevon(int servoPin, int trim) : Surface(servoPin, trim) {

}