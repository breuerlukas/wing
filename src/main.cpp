#include <Arduino.h>
#include "transmitter/transmitter.h"
#include "transmitter/channel/stick.h"
#include "transmitter/channel/dual-switch.h"
#include "transmitter/channel/triple-switch.h"
#include "transmitter/channel/knob.h"
#include "imu/imu.h"
#include "altimeter/altimeter.h"
#include "engine/engine.h"
#include "surface/surfaces.h"
#include "pid/pid.h"
#include "plane.h"

const int kThrottleStickId = 2;
const int kElevatorStickId = 1;
const int kAileronStickId = 0;
const int kRudderStickId = 3;
const int kEngineSwitchId = 4;
const int kStabilizationSwitchId = 5;
const int kRollStabilizationKnobId = 6;
const int kPitchStabilizationKnobId = 7;
const int kAutopilotSwitchId = 9;
const int kRightRuddervatorPin = 2;
const int kLeftRuddervatorPin = 3;
const int kEnginePin = 4;
const int kAileronPin = 5;

Plane* plane;
long previousTime;

void setup() {
  //Serial.begin(9600);
  Transmitter* transmitter = new Transmitter(new Stick(kThrottleStickId),
    new Stick(kElevatorStickId), new Stick(kAileronStickId),
    new Stick(kRudderStickId));
  DualSwitch* engineSwitch = new DualSwitch(kEngineSwitchId);
  transmitter->RegisterChannel(engineSwitch);
  TripleSwitch* stabilizationSwitch = new TripleSwitch(kStabilizationSwitchId);
  transmitter->RegisterChannel(stabilizationSwitch);
  DualSwitch* autopilotSwitch = new DualSwitch(kAutopilotSwitchId);
  transmitter->RegisterChannel(autopilotSwitch);
  Knob* rollStabilizationKnob = new Knob(kRollStabilizationKnobId);
  transmitter->RegisterChannel(rollStabilizationKnob);
  Knob* pitchStabilizationKnob = new Knob(kPitchStabilizationKnobId);
  transmitter->RegisterChannel(pitchStabilizationKnob);
  Imu* imu = new Imu();
  Altimeter* altimeter = new Altimeter(1013);
  Engine* engine = new Engine(kEnginePin);
  Surfaces* surfaces = new Surfaces(new Aileron(kAileronPin),
    new Ruddervator(kRightRuddervatorPin), new Ruddervator(kLeftRuddervatorPin));
  TinyGPSPlus* gps = new TinyGPSPlus();
  Location* planeLocation = new Location(0, 0);
  Pid* rollPidController = new Pid(0.7, 0, 0.05);
  Pid* pitchPidController = new Pid(1, 0, 0.1);
  Pid* verticalSpeedPidController = new Pid(1, 0, 0.1);
  Operation* operation = new Operation(transmitter, imu, altimeter, engine, surfaces,
    engineSwitch, stabilizationSwitch, rollStabilizationKnob,
    pitchStabilizationKnob, rollPidController, pitchPidController, verticalSpeedPidController);
  std::vector<Waypoint> waypoints;
  Mission* mission = new Mission(waypoints);
  Autopilot* autopilot = new Autopilot(transmitter, imu, engine, surfaces,
    autopilotSwitch, rollStabilizationKnob, pitchStabilizationKnob, gps,
    planeLocation, mission);
  plane = new Plane(transmitter, imu, altimeter, engine, surfaces, gps,
    planeLocation, operation, autopilot);
  plane->Initialize();
}

void loop() {
  long time = millis();
  if (previousTime + 10 > time) {
    return;
  }
  previousTime = time;
  plane->Tick();
}