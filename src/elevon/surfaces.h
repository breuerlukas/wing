#ifndef WING_SURFACES_H
#define WING_SURFACES_H

#include <ArduinoSTL.h>
#include "elevon.h"

class Surfaces {
private:
  Elevon* right_elevon_;
  Elevon* left_elevon_;
  std::vector<int> right_elevon_temp_values_;
  std::vector<int> left_elevon_temp_values_;
public:
  Surfaces(Elevon* rightElevon, Elevon* leftElevon);
  void Initialize();
  void PerformSyncMovement(int value);
  void PerformAsyncMovement(int value);
  void Flush();
};


#endif //WING_SURFACES_H
