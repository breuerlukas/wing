#ifndef PLANE_DIRECTION_H
#define PLANE_DIRECTION_H

class Direction {
private:
  float bearing_;
  double distance_;
public:
  Direction(float bearing, double distance);
  float Bearing();
  double Distance();
};


#endif //PLANE_DIRECTION_H
