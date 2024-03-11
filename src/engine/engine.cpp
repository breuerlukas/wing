#include "engine.h"

Engine::Engine(int pin) : esc_pin_(pin) {

}

void Engine::Initialize() {
  esc_.attach(esc_pin_, 1000, 2000);
}

void Engine::Idle() {
  ApplyThrust(1000);
}

void Engine::ApplyThrust(int thrust) {
  thrust_ = thrust;
  esc_.write(map(thrust, 1000, 2000, 0, 180));
}

int Engine::Thrust() {
  return thrust_;
}
