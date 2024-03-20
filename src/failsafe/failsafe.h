#ifndef WING_FAILSAFE_H
#define WING_FAILSAFE_H

#include "navigation/waypoint.h"

enum FailsafeState {
  kFailsafeEnabled,
  kFailsafeDisabled
};

class Failsafe {
private:
  Waypoint* home_waypoint_;
  FailsafeState state_ = kFailsafeDisabled;
public:
  Failsafe(Waypoint* homeWaypoint);
  void Check();
  FailsafeState State();
};


#endif //WING_FAILSAFE_H
