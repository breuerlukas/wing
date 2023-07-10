#ifndef WING_MISSION_H
#define WING_MISSION_H

#include <ArduinoSTL.h>
#include "waypoint.h"

class Mission {
private:
  std::vector<Waypoint> waypoints_;
  int waypoint_index_ = 0;
public:
  Mission(std::vector<Waypoint> waypoints);
  void Skip();
  void Direct();
  void Abort();
};


#endif //WING_MISSION_H
