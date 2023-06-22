#ifndef PLANE_MISSION_H
#define PLANE_MISSION_H

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


#endif //PLANE_MISSION_H
