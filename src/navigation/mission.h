#ifndef WING_MISSION_H
#define WING_MISSION_H

#include <ArduinoSTL.h>
#include "waypoint.h"

enum MissionStatus {
  kActive,
  kInactive
};

class Mission {
private:
  std::vector<Waypoint> waypoints_;
  int waypoint_index_ = 0;
  MissionStatus mission_status_ = kInactive;
public:
  Mission(std::vector<Waypoint> waypoints);
  void Begin();
  void Next();
  Waypoint Current();
  void Abort();
};


#endif //WING_MISSION_H
