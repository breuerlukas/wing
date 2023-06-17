#include "transmitter.h"

Transmitter::Transmitter(Stick* throttle_stick, Stick* elevator_stick, Stick
* aileron_stick) :
throttle_stick_(throttle_stick), elevator_stick_(elevator_stick), aileron_stick_(aileron_stick) {
  channels_.push_back(throttle_stick);
  channels_.push_back(elevator_stick);
  channels_.push_back(aileron_stick);
}

static byte rcOld;
volatile unsigned long rcRises[3];
volatile unsigned long rcTimes[3];

void Transmitter::Initialize() {
  for (Channel* channel : channels_) {
    channel->Initialize();
  }
  rcOld = 0;
  PCMSK1 |= 0x0F;
  PCIFR |= 0x02;
  PCICR |= 0x02;
}

ISR(PCINT1_vect) {
  byte rcNew = PINC & 15;
  byte changes = rcNew^rcOld;
  byte channel = 0;
  unsigned long now = micros();
  while (changes) {
    if ((changes & 1)) {
      if ((rcNew & (1<<channel))) {
        rcRises[channel] = now;
      } else {
        rcTimes[channel] = now - rcRises[channel];
      }
    }
    changes >>= 1;
    ++channel;
  }
  rcOld = rcNew;
}

void Transmitter::Update() {
  for (int i = 0; i < channels_.size(); i++) {
    channels_[i]->Update(rcTimes[i]);
  }
}

Stick* Transmitter::ThrottleStick() {
  return throttle_stick_;
}

Stick* Transmitter::ElevatorStick() {
  return elevator_stick_;
}

Stick* Transmitter::AileronStick() {
  return aileron_stick_;
}
