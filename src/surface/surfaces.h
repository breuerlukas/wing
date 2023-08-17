#ifndef WING_SURFACES_H
#define WING_SURFACES_H

#include <ArduinoSTL.h>
#include "aileron.h"
#include "ruddervator.h"

class Surfaces {
private:
  Aileron* right_aileron_;
  Aileron* left_aileron_;
  Ruddervator* right_ruddervator_;
  Ruddervator* left_ruddervator_;
  std::vector<int> right_aileron_temp_values_;
  std::vector<int> left_aileron_temp_values_;
  std::vector<int> right_ruddervator_temp_values_;
  std::vector<int> left_ruddervator_temp_values_;
  void FlushAilerons();
  void FlushRuddervators();
public:
  Surfaces(Aileron* rightAileron, Aileron* leftAileron,
    Ruddervator* rightRuddervator, Ruddervator* leftRuddervator);
  void Initialize();
  void PerformAsyncAileronMovement(int value);
  void PerformSyncRuddervatorMovement(int value);
  void PerformAsyncRuddervatorMovement(int value);
  void Flush();
};


#endif //WING_SURFACES_H
