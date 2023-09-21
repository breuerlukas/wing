#include "surfaces.h"

Surfaces::Surfaces(Aileron* aileron, Ruddervator* rightRuddervator,
   Ruddervator* leftRuddervator)
  : aileron_(aileron),
    right_ruddervator_(rightRuddervator),
    left_ruddervator_(leftRuddervator) {

}

void Surfaces::Initialize() {
  aileron_->Initialize();
  right_ruddervator_->Initialize();
  left_ruddervator_->Initialize();
}

void Surfaces::PerformAsyncAileronMovement(int value) {
  aileron_temp_values_.add(value);
}

void Surfaces::PerformSyncRuddervatorMovement(int value) {
  right_ruddervator_temp_values_.add(value);
  left_ruddervator_temp_values_.add(-value);
}

void Surfaces::PerformAsyncRuddervatorMovement(int value) {
  right_ruddervator_temp_values_.add(value);
  left_ruddervator_temp_values_.add(value);
}

void Surfaces::Flush() {
  FlushAilerons();
  FlushRuddervators();
}

void Surfaces::FlushAilerons() {
  int accumulated = 90;
  for (int i = 0; i < aileron_temp_values_.size(); i++) {
    accumulated += aileron_temp_values_.get(i);
  }
  aileron_temp_values_.clear();
  accumulated = MIN(MAX(accumulated, 0), 180);
  aileron_->Move(accumulated);
}

void Surfaces::FlushRuddervators() {
  int accumulatedRight = 90;
  for (int i = 0; i < right_ruddervator_temp_values_.size(); i++) {
    accumulatedRight += right_ruddervator_temp_values_.get(i);
  }
  right_ruddervator_temp_values_.clear();
  int accumulatedLeft = 90;
  for (int i = 0; i < left_ruddervator_temp_values_.size(); i++) {
    accumulatedLeft += left_ruddervator_temp_values_.get(i);
  }
  left_ruddervator_temp_values_.clear();
  accumulatedRight = MIN(MAX(accumulatedRight, 0), 180);
  accumulatedLeft = MIN(MAX(accumulatedLeft, 0), 180);
  right_ruddervator_->Move(accumulatedRight);
  left_ruddervator_->Move(accumulatedLeft);
}