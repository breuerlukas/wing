#include "surface-compound.h"

void SurfaceCompound::RegisterLineSurface(Surface* surface) {
  line_surfaces_.add(surface);
  type_ = kLineCompound;
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
  if (IsLineCompound()) {
    InitializeLineSurfaces();
  } else if (IsSideCompound()) {
    InitializeSideSurfaces();
  }
}

void SurfaceCompound::InitializeLineSurfaces() {
  for (int i = 0; i < line_surfaces_.size(); i++) {
    line_surfaces_.get(i)->Initialize();
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

void SurfaceCompound::PerformSyncSideSurfaceMovement(int value) {
  if (!IsSideCompound()) {
    return;
  }
  PerformSideSurfaceMovement(value, kSideLeft);
  PerformSideSurfaceMovement(-value, kSideRight);
}

void SurfaceCompound::PerformAsyncSideSurfaceMovement(int value) {
  if (!IsSideCompound()) {
    return;
  }
  PerformSideSurfaceMovement(-value, kSideLeft);
  PerformSideSurfaceMovement(-value, kSideRight);
}

void SurfaceCompound::PerformLineSurfaceMovement(int value) {
  line_temp_values_.add(value);
}

void SurfaceCompound::PerformSideSurfaceMovement(int value, SurfaceSide side) {
  if (side == kSideLeft) {
    left_temp_values_.add(value);
  } else {
    right_temp_values_.add(value);
  }
}

void SurfaceCompound::Flush() {
  if (IsLineCompound()) {
    FlushLineSurfaces();
  } else if (IsSideCompound()) {
    FlushSideSurfaces();
  }
}

void SurfaceCompound::FlushLineSurfaces() {
  int value = CalculateAccumulatedValue(line_temp_values_);
  line_temp_values_.clear();
  for (int i = 0; i < line_surfaces_.size(); i++) {
    line_surfaces_.get(i)->Move(value);
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

bool SurfaceCompound::IsLineCompound() {
  return type_ == kLineCompound;
}

bool SurfaceCompound::IsSideCompound() {
  return type_ == kSideCompound;
}
