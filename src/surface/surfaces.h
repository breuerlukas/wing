#ifndef WING_SURFACES_H
#define WING_SURFACES_H

#include "list/SimpleList.h"
#include "limits/limits.h"
#include "aileron.h"
#include "ruddervator.h"

class Surfaces {
private:
  Aileron* aileron_;
  Ruddervator* right_ruddervator_;
  Ruddervator* left_ruddervator_;
  SimpleList<int> aileron_temp_values_;
  SimpleList<int> right_ruddervator_temp_values_;
  SimpleList<int> left_ruddervator_temp_values_;
  void FlushAilerons();
  void FlushRuddervators();
public:
  Surfaces(Aileron* aileron, Ruddervator* rightRuddervator,
    Ruddervator* leftRuddervator);
  void Initialize();
  void PerformAsyncAileronMovement(int value);
  void PerformSyncRuddervatorMovement(int value);
  void PerformAsyncRuddervatorMovement(int value);
  void Flush();
};


#endif //WING_SURFACES_H
