#include "surfaces.h"

Surfaces::Surfaces() {

}

#ifdef AILERON
void Surfaces::RegisterAileron(Aileron *aileron) {
  aileron_compound_.RegisterLineSurface(aileron);
}

void Surfaces::RegisterLeftAileron(Aileron *aileron) {
  aileron_compound_.RegisterSideSurface(aileron, kSideLeft);
}

void Surfaces::RegisterRightAileron(Aileron *aileron) {
  aileron_compound_.RegisterSideSurface(aileron, kSideRight);
}
#endif

#ifdef ELEVATOR
void Surfaces::RegisterElevator(Elevator* elevator) {
  elevator_compound_.RegisterLineSurface(elevator);
}
#endif

#ifdef RUDDER
void Surfaces::RegisterRudder(Rudder* rudder) {
  rudder_compound_.RegisterLineSurface(rudder);
}
#endif

#ifdef ELEVON
void Surfaces::RegisterLeftElevon(Elevon* elevon) {
  elevon_compound_.RegisterSideSurface(elevon, kSideLeft);
}

void Surfaces::RegisterRightElevon(Elevon* elevon) {
  elevon_compound_.RegisterSideSurface(elevon, kSideRight);
}
#endif

#ifdef RUDDERVATOR
void Surfaces::RegisterLeftRuddervator(Ruddervator* ruddervator) {
  ruddervator_compound_.RegisterSideSurface(ruddervator, kSideLeft);
}

void Surfaces::RegisterRightRuddervator(Ruddervator* ruddervator) {
  ruddervator_compound_.RegisterSideSurface(ruddervator, kSideRight);
}
#endif

void Surfaces::Initialize() {
#ifdef AILERON
  aileron_compound_.Initialize();
#endif
#ifdef ELEVATOR
  elevator_compound_.Initialize();
#endif
#ifdef RUDDER
  rudder_compound_.Initialize();
#endif
#ifdef ELEVON
  elevon_compound_.Initialize();
#endif
#ifdef RUDDERVATOR
  ruddervator_compound_.Initialize();
#endif
}

#ifdef AILERON
void Surfaces::PerformAileronMovement(int value) {
  aileron_compound_.PerformLineSurfaceMovement(value);
}
#endif

#ifdef ELEVATOR
void Surfaces::PerformElevatorMovement(int value) {
  elevator_compound_.PerformLineSurfaceMovement(value);
}
#endif

#ifdef RUDDER
void Surfaces::PerformRudderMovement(int value) {
  rudder_compound_.PerformLineSurfaceMovement(value);
}
#endif

#ifdef ELEVON
void Surfaces::PerformSyncElevonMovement(int value) {
  elevon_compound_.PerformSyncSideSurfaceMovement(value);
}

void Surfaces::PerformAsyncElevonMovement(int value) {
  elevon_compound_.PerformAsyncSideSurfaceMovement(value);
}
#endif

#ifdef RUDDERVATOR
void Surfaces::PerformSyncRuddervatorMovement(int value) {
  ruddervator_compound_.PerformSyncSideSurfaceMovement(value);
}

void Surfaces::PerformAsyncRuddervatorMovement(int value) {
  ruddervator_compound_.PerformAsyncSideSurfaceMovement(value);
}
#endif

void Surfaces::Flush() {
#ifdef AILERON
  aileron_compound_.Flush();
#endif
#ifdef ELEVATOR
  elevator_compound_.Flush();
#endif
#ifdef RUDDER
  rudder_compound_.Flush();
#endif
#ifdef ELEVON
  elevon_compound_.Flush();
#endif
#ifdef RUDDERVATOR
  ruddervator_compound_.Flush();
#endif
}
