#include "engine.h"

Engine::Engine(int pin) : esc_pin_(pin) {

}

void Engine::Initialize() {
  esc_.attach(esc_pin_);
}

void Engine::ApplyThrust(int thrust) {
  thrust_ = thrust;
  esc_.write(thrust);
}

int Engine::Thrust() {
  return thrust_;
}
