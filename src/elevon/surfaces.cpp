#include "surfaces.h"

Surfaces::Surfaces(Elevon* right_elevon, Elevon* left_elevon)
: right_elevon_(right_elevon), left_elevon_(left_elevon) {

}

void Surfaces::Initialize() {
  right_elevon_->Initialize();
  left_elevon_->Initialize();
}

void Surfaces::PerformSyncMovement(int value) {
  StoreElevonsMovement(right_elevon_, value);
  StoreElevonsMovement(left_elevon_, -value);
}

void Surfaces::PerformAsyncMovement(int value) {
  StoreElevonsMovement(right_elevon_, value);
  StoreElevonsMovement(left_elevon_, value);
}

void Surfaces::StoreElevonsMovement(Elevon* elevon, int value) {
  if (elevon == right_elevon_) {
    right_elevon_temp_values_.push_back(value);
    return;
  }
  if (elevon == left_elevon_) {
    left_elevon_temp_values_.push_back(value);
    return;
  }
}

void Surfaces::Flush() {
  int accumulatedRight = 90;
  for (int value : right_elevon_temp_values_) {
    accumulatedRight += value;
  }
  right_elevon_temp_values_.clear();
  int accumulatedLeft = 90;
  for (int value : left_elevon_temp_values_) {
    accumulatedLeft += value;
  }
  left_elevon_temp_values_.clear();
  accumulatedRight = std::min(std::max(accumulatedRight, 0), 180);
  accumulatedLeft = std::min(std::max(accumulatedLeft, 0), 180);
  right_elevon_->Move(accumulatedRight);
  left_elevon_->Move(accumulatedLeft);
}
