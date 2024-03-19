#ifndef WING_SURFACES_H
#define WING_SURFACES_H

#include "list/list.h"
#include "config/config.h"
#include "surface/surface-compound.h"
#include "surface/aileron.h"
#include "surface/elevator.h"
#include "surface/rudder.h"
#include "surface/elevon.h"
#include "surface/ruddervator.h"

class Surfaces {
private:
#ifdef AILERON
  SurfaceCompound aileron_compound_;
#endif
#ifdef ELEVATOR
  SurfaceCompound elevator_compound_;
#endif
#ifdef RUDDER
  SurfaceCompound rudder_compound_;
#endif
#ifdef ELEVON
  SurfaceCompound elevon_compound_;
#endif
#ifdef RUDDERVATOR
  SurfaceCompound ruddervator_compound_;
#endif
public:
  Surfaces();
#ifdef AILERON
  void RegisterAileron(Aileron* aileron);
  void RegisterLeftAileron(Aileron* aileron);
  void RegisterRightAileron(Aileron* aileron);
#endif
#ifdef ELEVATOR
  void RegisterElevator(Elevator* elevator);
#endif
#ifdef RUDDER
  void RegisterRudder(Rudder* rudder);
#endif
#ifdef ELEVON
  void RegisterLeftElevon(Elevon* elevon);
  void RegisterRightElevon(Elevon* elevon);
#endif
#ifdef RUDDERVATOR
  void RegisterLeftRuddervator(Ruddervator* ruddervator);
  void RegisterRightRuddervator(Ruddervator* ruddervator);
#endif
  void Initialize();
#ifdef AILERON
  void PerformAileronMovement(int value);
#endif
#ifdef ELEVATOR
  void PerformElevatorMovement(int value);
#endif
#ifdef RUDDER
  void PerformRudderMovement(int value);
#endif
#ifdef ELEVON
  void PerformSyncElevonMovement(int value);
  void PerformAsyncElevonMovement(int value);
#endif
#ifdef RUDDERVATOR
  void PerformSyncRuddervatorMovement(int value);
  void PerformAsyncRuddervatorMovement(int value);
#endif
  void Flush();
};


#endif //WING_SURFACES_H
