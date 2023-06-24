#include "channel.h"

Channel::Channel(int id) : id_(id) {

}

void Channel::Update(long value) {
  if (value == 0) {
    return;
  }
  this->value = value;
}

int Channel::Id() {
  return id_;
}