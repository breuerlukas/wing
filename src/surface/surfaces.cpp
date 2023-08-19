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
  aileron_temp_values_.push_back(value);
}

void Surfaces::PerformSyncRuddervatorMovement(int value) {
  right_ruddervator_temp_values_.push_back(value);
  left_ruddervator_temp_values_.push_back(-value);
}

void Surfaces::PerformAsyncRuddervatorMovement(int value) {
  right_ruddervator_temp_values_.push_back(value);
  left_ruddervator_temp_values_.push_back(value);
}

void Surfaces::Flush() {
  FlushAilerons();
  FlushRuddervators();
}

void Surfaces::FlushAilerons() {
  int accumulated = 90;
  for (int value : aileron_temp_values_) {
    accumulated += value;
  }
  aileron_temp_values_.clear();
  accumulated = std::min(std::max(accumulated, 0), 180);
  aileron_->Move(accumulated);
}

void Surfaces::FlushRuddervators() {
  int accumulatedRight = 90;
  for (int value : right_ruddervator_temp_values_) {
    accumulatedRight += value;
  }
  right_ruddervator_temp_values_.clear();
  int accumulatedLeft = 90;
  for (int value : left_ruddervator_temp_values_) {
    accumulatedLeft += value;
  }
  left_ruddervator_temp_values_.clear();
  accumulatedRight = std::min(std::max(accumulatedRight, 0), 180);
  accumulatedLeft = std::min(std::max(accumulatedLeft, 0), 180);
  right_ruddervator_->Move(accumulatedRight);
  left_ruddervator_->Move(accumulatedLeft);
}