#ifndef WING_SURFACECOMPOUND_H
#define WING_SURFACECOMPOUND_H

#include "list/list.h"
#include "surface/surface.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

enum SurfaceCompoundType {
  kSingleCompound,
  kMultipleCompound,
  kSideCompound
};

enum SurfaceSide {
  kSideLeft,
  kSideRight
};

class SurfaceCompound {
private:
  SurfaceCompoundType type_;
  Surface* single_surface_;
  List<Surface*> multiple_surfaces_;
  List<Surface*> left_surfaces_;
  List<Surface*> right_surfaces_;
  List<int> single_temp_values_;
  List<int> multiple_temp_values_;
  List<int> left_temp_values_;
  List<int> right_temp_values_;
  int CalculateAccumulatedValue(List<int> tempValues);
  void InitializeSingleSurface();
  void InitializeMultipleSurfaces();
  void InitializeSideSurfaces();
  void PerformSingleSurfaceMovement(int value);
  void PerformMultipleSurfaceMovement(int value);
  void PerformSideSurfaceMovement(int value, SurfaceSide side);
  void FlushSingleSurface();
  void FlushMultipleSurfaces();
  void FlushSideSurfaces();
public:
  void RegisterSingleSurface(Surface* surface);
  void RegisterMultipleSurface(Surface* surface);
  void RegisterSideSurface(Surface* surface, SurfaceSide side);
  void PerformMovement(int value);
  void PerformSyncMovement(int value);
  void PerformAsyncMovement(int value);
  void Initialize();
  void Flush();
  bool IsSingleCompound();
  bool IsMultipleCompound();
  bool IsSideCompound();
  Surface* SingleSurface();
  List<Surface*> MultipleSurfaces();
  List<Surface*> LeftSurfaces();
  List<Surface*> RightSurfaces();
};

#endif //WING_SURFACECOMPOUND_H
