#include "surface-compound.h"

void SurfaceCompound::RegisterSingleSurface(Surface* surface) {
  single_surface_ = surface;
  type_ = kSingleCompound;
}

void SurfaceCompound::RegisterMultipleSurface(Surface* surface) {
  multiple_surfaces_.add(surface);
  type_ = kMultipleCompound;
}

void SurfaceCompound::RegisterSideSurface(Surface* surface, SurfaceSide side) {
  if (side == kSideLeft) {
    left_surfaces_.add(surface);
  } else {
    right_surfaces_.add(surface);
  }
  type_ = kSideCompound;
}

void SurfaceCompound::Initialize() {
  if (IsSingleCompound()) {
    InitializeSingleSurface();
  } else if (IsMultipleCompound()) {
    InitializeMultipleSurfaces();
  } else if (IsSideCompound()) {
    InitializeSideSurfaces();
  }
}

void SurfaceCompound::InitializeSingleSurface() {
  single_surface_->Initialize();
}

void SurfaceCompound::InitializeMultipleSurfaces() {
  for (int i = 0; i < multiple_surfaces_.size(); i++) {
    multiple_surfaces_.get(i)->Initialize();
  }
}

void SurfaceCompound::InitializeSideSurfaces() {
  for (int i = 0; i < left_surfaces_.size(); i++) {
    left_surfaces_.get(i)->Initialize();
  }
  for (int i = 0; i < right_surfaces_.size(); i++) {
    right_surfaces_.get(i)->Initialize();
  }
}

void SurfaceCompound::PerformMovement(int value) {
  if (IsSingleCompound()) {
    PerformSingleSurfaceMovement(value);
  } else if (IsMultipleCompound()) {
    PerformMultipleSurfaceMovement(value);
  }
}

void SurfaceCompound::PerformSyncMovement(int value) {
  if (!IsSideCompound()) {
    return;
  }
  PerformSideSurfaceMovement(value, kSideLeft);
  PerformSideSurfaceMovement(-value, kSideRight);
}

void SurfaceCompound::PerformAsyncMovement(int value) {
  if (!IsSideCompound()) {
    return;
  }
  PerformSideSurfaceMovement(value, kSideLeft);
  PerformSideSurfaceMovement(value, kSideRight);
}

void SurfaceCompound::PerformSingleSurfaceMovement(int value) {
  single_temp_values_.add(value);
}

void SurfaceCompound::PerformMultipleSurfaceMovement(int value) {
  multiple_temp_values_.add(value);
}

void SurfaceCompound::PerformSideSurfaceMovement(int value, SurfaceSide side) {
  if (side == kSideLeft) {
    left_temp_values_.add(value);
  } else {
    right_temp_values_.add(value);
  }
}

void SurfaceCompound::Flush() {
  if (IsSingleCompound()) {
    FlushSingleSurface();
  } else if (IsMultipleCompound()) {
    FlushMultipleSurfaces();
  } else if (IsSideCompound()) {
    FlushSideSurfaces();
  }
}

void SurfaceCompound::FlushSingleSurface() {
  int value = CalculateAccumulatedValue(single_temp_values_);
  single_temp_values_.clear();
  single_surface_->Move(value);
}

void SurfaceCompound::FlushMultipleSurfaces() {
  int value = CalculateAccumulatedValue(multiple_temp_values_);
  multiple_temp_values_.clear();
  for (int i = 0; i < multiple_surfaces_.size(); i++) {
    multiple_surfaces_.get(i)->Move(value);
  }
}

void SurfaceCompound::FlushSideSurfaces() {
  int leftValue = CalculateAccumulatedValue(left_temp_values_);
  left_temp_values_.clear();
  for (int i = 0; i < left_surfaces_.size(); i++) {
    left_surfaces_.get(i)->Move(leftValue);
  }
  int rightValue = CalculateAccumulatedValue(right_temp_values_);
  right_temp_values_.clear();
  for (int i = 0; i < right_surfaces_.size(); i++) {
    right_surfaces_.get(i)->Move(rightValue);
  }
}

int SurfaceCompound::CalculateAccumulatedValue(List<int> tempValues) {
  int accumulated = 90;
  for (int i = 0; i < tempValues.size(); i++) {
    accumulated += tempValues.get(i);
  }
  accumulated = MIN(MAX(accumulated, 0), 180);
  return accumulated;
}

bool SurfaceCompound::IsSingleCompound() {
  return type_ == kSingleCompound;
}

bool SurfaceCompound::IsMultipleCompound() {
  return type_ == kMultipleCompound;
}

bool SurfaceCompound::IsSideCompound() {
  return type_ == kSideCompound;
}

Surface *SurfaceCompound::SingleSurface() {
  return single_surface_;
}

List<Surface*> SurfaceCompound::MultipleSurfaces() {
  return multiple_surfaces_;
}

List<Surface*> SurfaceCompound::LeftSurfaces() {
  return left_surfaces_;
}

List<Surface*> SurfaceCompound::RightSurfaces() {
  return right_surfaces_;
}
