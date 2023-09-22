#include "mission.h"

Mission::Mission() {

}

void Mission::AddWaypoint(Waypoint *waypoint) {
  waypoints_.add(waypoint);
}

void Mission::RemoveWaypoint(Waypoint *waypoint) {
  waypoints_.remove(waypoints_.search(waypoint));
}

void Mission::Begin() {
  mission_status_ = kActive;
}

void Mission::Next() {
  if (waypoint_index_ + 1 == waypoints_.size()) {
    Abort();
    return;
  }
  waypoint_index_++;
}

Waypoint* Mission::Current() {
  return waypoints_.get(waypoint_index_);
}

void Mission::Abort() {
  mission_status_ = kInactive;
}

MissionStatus Mission::Status() {
  return mission_status_;
}