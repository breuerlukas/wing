#include <Arduino.h>
#include "transmitter/transmitter.h"
#include "transmitter/channel/stick.h"
#include "transmitter/channel/dual-switch.h"
#include "transmitter/channel/triple-switch.h"
#include "imu/imu.h"
#include "altimeter/altimeter.h"
#include "engine/engine.h"
#include "surface/surfaces.h"
#include "pid/pid.h"
#include "led/led.h"
#include "plane.h"

const int kThrottleStickId = 2;
const int kElevatorStickId = 1;
const int kAileronStickId = 0;
const int kRudderStickId = 3;
const int kEngineSwitchId = 7;
const int kStabilizationSwitchId = 5;
const int kAutopilotSwitchId = 6;
const int kAutopilotModeSwitchId = 4;
const int kEnginePin = 2;
const int kAileronPin = 3;
const int kRightRuddervatorPin = 4;
const int kLeftRuddervatorPin = 5;

Plane* plane;

void setup() {
  Transmitter* transmitter = new Transmitter(new Stick(kThrottleStickId),
    new Stick(kElevatorStickId), new Stick(kAileronStickId),
    new Stick(kRudderStickId));
  DualSwitch* engineSwitch = new DualSwitch(kEngineSwitchId);
  transmitter->RegisterChannel(engineSwitch);
  TripleSwitch* stabilizationSwitch = new TripleSwitch(kStabilizationSwitchId);
  transmitter->RegisterChannel(stabilizationSwitch);
  DualSwitch* autopilotSwitch = new DualSwitch(kAutopilotSwitchId);
  transmitter->RegisterChannel(autopilotSwitch);
  TripleSwitch* autopilotModeSwitch = new TripleSwitch(kAutopilotModeSwitchId);
  transmitter->RegisterChannel(autopilotModeSwitch);
  Imu* imu = new Imu();
  Altimeter* altimeter = new Altimeter(1013);
  Engine* engine = new Engine(kEnginePin);
  Surfaces* surfaces = new Surfaces(new Aileron(kAileronPin),
    new Ruddervator(kRightRuddervatorPin), new Ruddervator(kLeftRuddervatorPin));
  Location* planeLocation = new Location(0, 0);
  Pid* rollPidController = new Pid(0.7, 0, 0.05);
  Pid* pitchPidController = new Pid(1, 0, 0.1);
  Operation* operation = new Operation(transmitter, imu, engine, surfaces,
    engineSwitch, stabilizationSwitch, rollPidController, pitchPidController);
  Mission* mission = new Mission();
  mission->AddWaypoint(new Waypoint(Location(50.75672023285704, 7.114160700111882), 30.0));
  Autopilot* autopilot = new Autopilot(transmitter, imu, altimeter, engine, surfaces,
    engineSwitch, autopilotSwitch, autopilotModeSwitch, rollPidController,
    pitchPidController, planeLocation, mission);
  Led* led = new Led(13);
  plane = new Plane(transmitter, imu, altimeter, engine, surfaces,
    planeLocation, operation, autopilot, led);
  plane->Initialize();
}

void loop() {
  plane->Tick();
}