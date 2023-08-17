#include <Arduino.h>
#include "transmitter/transmitter.h"
#include "transmitter/channel/stick.h"
#include "transmitter/channel/switch.h"
#include "transmitter/channel/knob.h"
#include "motion/motion.h"
#include "motion/imu.h"
#include "engine/engine.h"
#include "surface/surfaces.h"
#include "plane.h"

const int kThrottleStickId = 2;
const int kElevatorStickId = 1;
const int kAileronStickId = 0;
const int kRudderStickId = 3;
const int kEngineSwitchId = 4;
const int kStabilizationSwitchId = 5;
const int kRollStabilizationKnobId = 6;
const int kPitchStabilizationKnobId = 7;
const int kPitchStabilizationSwitchId = 8;
const int kAutopilotSwitchId = 9;
const int kEnginePin = 4;
const int kRightAileronPin = 2;
const int kLeftAileronPin = 3;
const int kRightRuddervatorPin = 4;
const int kLeftRuddervatorPin = 5;

Plane* plane;

void setup() {
  //Serial.begin(115200);
  Transmitter* transmitter = new Transmitter(new Stick(kThrottleStickId),
    new Stick(kElevatorStickId), new Stick(kAileronStickId),
    new Stick(kRudderStickId));
  Switch* engineSwitch = new Switch(kEngineSwitchId);
  transmitter->RegisterChannel(engineSwitch);
  Switch* stabilizationSwitch = new Switch(kStabilizationSwitchId);
  transmitter->RegisterChannel(stabilizationSwitch);
  Switch* pitchStabilizationSwitch = new Switch(kPitchStabilizationSwitchId);
  transmitter->RegisterChannel(pitchStabilizationSwitch);
  Knob* rollStabilizationKnob = new Knob(kRollStabilizationKnobId);
  transmitter->RegisterChannel(rollStabilizationKnob);
  Knob* pitchStabilizationKnob = new Knob(kPitchStabilizationKnobId);
  transmitter->RegisterChannel(pitchStabilizationKnob);
  Motion* motion = new Motion();
  Imu* imu = new Imu();
  Engine* engine = new Engine(kEnginePin);
  Surfaces* surfaces = new Surfaces(new Aileron(kRightAileronPin),
    new Aileron(kLeftAileronPin), new Ruddervator(kRightRuddervatorPin),
    new Ruddervator(kLeftRuddervatorPin));
  TinyGPSPlus* gps = new TinyGPSPlus();
  Location* planeLocation = new Location(0, 0);
  Operation* operation = new Operation(transmitter, imu, /*motion, */engine, surfaces,
    engineSwitch, stabilizationSwitch, pitchStabilizationSwitch,
    rollStabilizationKnob, pitchStabilizationKnob);
  Switch* autopilotSwitch = new Switch(kAutopilotSwitchId);
  transmitter->RegisterChannel(autopilotSwitch);
  std::vector<Waypoint> waypoints;
  Mission* mission = new Mission(waypoints);
  Autopilot* autopilot = new Autopilot(transmitter, motion, engine, surfaces,
    autopilotSwitch, rollStabilizationKnob, pitchStabilizationKnob, gps, planeLocation, mission);
  plane = new Plane(transmitter, imu, /*motion, */engine, surfaces, gps, planeLocation, operation, autopilot);
  plane->Initialize();
}

void loop() {
  plane->Tick();
}