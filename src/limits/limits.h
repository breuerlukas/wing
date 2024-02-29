#ifndef WING_LIMITS_H
#define WING_LIMITS_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MAX_BANK_ANGLE 80
#define AUTOPILOT_MAX_BANK_ANGLE 45
#define MAX_CLIMB_ANGLE 50
#define MAX_DESCENT_ANGLE 30
#define AUTOPILOT_MAX_CLIMB_ANGLE 25
#define AUTOPILOT_MAX_DESCENT_ANGLE 15
#define DISTANCE_TO_WAYPOINT_TO_SKIP 20

#endif //WING_LIMITS_H
