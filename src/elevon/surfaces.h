#ifndef PLANE_SURFACES_H
#define PLANE_SURFACES_H

#include <ArduinoSTL.h>
#include "elevon.h"

class Surfaces {
private:
  Elevon* right_elevon_;
  Elevon* left_elevon_;
  std::vector<int> right_elevon_temp_values_;
  std::vector<int> left_elevon_temp_values_;
public:
  Surfaces(Elevon* right_elevon_, Elevon* left_elevon_);
  void Initialize();
  void PerformSyncMovement(int value);
  void PerformAsyncMovement(int value);
  void Flush();
};


#endif //PLANE_SURFACES_H
