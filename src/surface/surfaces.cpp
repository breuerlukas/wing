#include "surfaces.h"

Surfaces::Surfaces(Aileron* rightAileron, Aileron* leftAileron,
  Ruddervator* rightRuddervator, Ruddervator* leftRuddervator)
  : right_aileron_(rightAileron),
    left_aileron_(leftAileron),
    right_ruddervator_(rightRuddervator),
    left_ruddervator_(leftRuddervator) {

}

void Surfaces::Initialize() {
  right_aileron_->Initialize();
  left_aileron_->Initialize();
  right_ruddervator_->Initialize();
  left_ruddervator_->Initialize();
}

void Surfaces::PerformAsyncAileronMovement(int value) {
  right_aileron_temp_values_.push_back(value);
  left_aileron_temp_values_.push_back(value);
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
  int accumulatedRight = 90;
  for (int value : right_aileron_temp_values_) {
    accumulatedRight += value;
  }
  right_aileron_temp_values_.clear();
  int accumulatedLeft = 90;
  for (int value : left_aileron_temp_values_) {
    accumulatedLeft += value;
  }
  left_aileron_temp_values_.clear();
  accumulatedRight = std::min(std::max(accumulatedRight, 0), 180);
  accumulatedLeft = std::min(std::max(accumulatedLeft, 0), 180);
  right_aileron_->Move(accumulatedRight);
  left_aileron_->Move(accumulatedLeft);
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