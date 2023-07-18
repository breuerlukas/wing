#ifndef WING_DIRECTION_H
#define WING_DIRECTION_H

class Direction {
private:
  double bearing_;
  double distance_;
public:
  Direction(double bearing, double distance);
  double Bearing();
  double Distance();
};


#endif //WING_DIRECTION_H
