#ifndef WING_MISSION_H
#define WING_MISSION_H

#include "list/list.h"
#include "waypoint.h"

enum MissionStatus {
  kActive,
  kInactive
};

class Mission {
private:
  List<Waypoint*> waypoints_;
  int waypoint_index_ = 0;
  MissionStatus mission_status_ = kInactive;
public:
  Mission();
  void AddWaypoint(Waypoint* waypoint);
  void RemoveWaypoint(Waypoint* waypoint);
  void Begin();
  void Next();
  Waypoint* Current();
  void Abort();
  MissionStatus Status();
};


#endif //WING_MISSION_H
