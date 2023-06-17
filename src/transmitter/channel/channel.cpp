#include "channel.h"

Channel::Channel(int pin) : pin_(pin) {

}

void Channel::Initialize() {
  pinMode(pin_, INPUT);
}

void Channel::Update(long value) {
  this->value = value;
}

long Channel::Read() {
  return value;
}

int Channel::Pin() {
  return pin_;
}