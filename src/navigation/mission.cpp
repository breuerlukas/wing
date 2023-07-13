#include "mission.h"

Mission::Mission(std::vector<Waypoint> waypoints) : waypoints_(waypoints) {

}

void Mission::Begin() {
  mission_status_ = kActive;
}

void Mission::Next() {
  waypoint_index_++;
}

Waypoint Mission::Current() {
  return waypoints_[waypoint_index_];
}

void Mission::Abort() {
  mission_status_ = kInactive;
}

MissionStatus Mission::Status() {
  return mission_status_;
}