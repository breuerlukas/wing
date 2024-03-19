#ifndef WING_SURFACECOMPOUND_H
#define WING_SURFACECOMPOUND_H

#include "list/list.h"
#include "surface/surface.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

enum SurfaceCompoundType {
  kLineCompound,
  kSideCompound
};

enum SurfaceSide {
  kSideLeft,
  kSideRight
};

class SurfaceCompound {
private:
  SurfaceCompoundType type_;
  List<Surface*> line_surfaces_;
  List<Surface*> left_surfaces_;
  List<Surface*> right_surfaces_;
  List<int> line_temp_values_;
  List<int> left_temp_values_;
  List<int> right_temp_values_;
  int CalculateAccumulatedValue(List<int> tempValues);
  void InitializeLineSurfaces();
  void InitializeSideSurfaces();
  void PerformSideSurfaceMovement(int value, SurfaceSide side);
  void FlushLineSurfaces();
  void FlushSideSurfaces();
public:
  void RegisterLineSurface(Surface* surface);
  void RegisterSideSurface(Surface* surface, SurfaceSide side);
  void PerformLineSurfaceMovement(int value);
  void PerformSyncSideSurfaceMovement(int value);
  void PerformAsyncSideSurfaceMovement(int value);
  void Initialize();
  void Flush();
  bool IsLineCompound();
  bool IsSideCompound();
};

#endif //WING_SURFACECOMPOUND_H
