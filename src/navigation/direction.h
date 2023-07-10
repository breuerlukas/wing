#ifndef WING_DIRECTION_H
#define WING_DIRECTION_H

class Direction {
private:
  float bearing_;
  double distance_;
public:
  Direction(float bearing, double distance);
  float Bearing();
  double Distance();
};


#endif //WING_DIRECTION_H
