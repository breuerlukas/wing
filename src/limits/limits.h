#ifndef WING_LIMITS_H
#define WING_LIMITS_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define MAX_BANK_ANGLE 70
#define AUTOPILOT_MAX_BANK_ANGLE MAX_BANK_ANGLE / 2.0
#define MAX_PITCH_ANGLE 50
#define MIN_PITCH_ANGLE 30
#define DISTANCE_TO_WAYPOINT_TO_SKIP 5

#endif //WING_LIMITS_H
