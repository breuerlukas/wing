#include <Arduino.h>
#include "transmitter/transmitter.h"
#include "transmitter/channel/stick.h"
#include "transmitter/channel/switch.h"
#include "transmitter/channel/knob.h"
#include "motion/motion.h"
#include "engine/engine.h"
#include "elevon/surfaces.h"
#include "plane.h"

const int kThrottleStickId = 2;
const int kElevatorStickId = 1;
const int kAileronStickId = 0;
const int kEngineSwitchId = 4;
const int kStabilizationSwitchId = 5;
const int kRollStabilizationKnobId = 6;
const int kPitchStabilizationKnobId = 7;
const int kAutopilotSwitchId = 8;
const int kEnginePin = 4;
const int kRightElevonPin = 2;
const int kLeftElevonPin = 3;

Plane* plane;

void setup() {
  Serial.begin(115200);
  Transmitter* transmitter = new Transmitter(new Stick(kThrottleStickId),
    new Stick(kElevatorStickId), new Stick(kAileronStickId));
  Switch* engineSwitch = new Switch(kEngineSwitchId);
  transmitter->RegisterChannel(engineSwitch);
  Switch* stabilizationSwitch = new Switch(kStabilizationSwitchId);
  transmitter->RegisterChannel(stabilizationSwitch);
  Knob* rollStabilizationKnob = new Knob(kRollStabilizationKnobId);
  transmitter->RegisterChannel(rollStabilizationKnob);
  Knob* pitchStabilizationKnob = new Knob(kPitchStabilizationKnobId);
  transmitter->RegisterChannel(pitchStabilizationKnob);
  Motion* motion = new Motion();
  Engine* engine = new Engine(kEnginePin);
  Surfaces* surfaces = new Surfaces(new Elevon(kRightElevonPin),
    new Elevon(kLeftElevonPin));
  Location* planeLocation = new Location(0, 0);
  Operation* operation = new Operation(transmitter, motion, engine, surfaces,
    engineSwitch, stabilizationSwitch, rollStabilizationKnob, pitchStabilizationKnob);
  Switch* autopilotSwitch = new Switch(kAutopilotSwitchId);
  transmitter->RegisterChannel(autopilotSwitch);
  std::vector<Waypoint> waypoints;
  Mission* mission = new Mission(waypoints);
  Autopilot* autopilot = new Autopilot(transmitter, motion, engine, surfaces,
    autopilotSwitch, rollStabilizationKnob, pitchStabilizationKnob, planeLocation, mission);
  plane = new Plane(transmitter, motion, engine, surfaces, planeLocation, operation, autopilot);
  plane->Initialize();
}

void loop() {
  plane->Tick();
}