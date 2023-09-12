#include "crsf.h"
#include <Arduino.h>

CRSF::CRSF(HardwareSerial &serial) : serial_(serial) {

}

void CRSF::Begin(unsigned long baud) {
  for (int i = 0; i < 16; i++) {
    channels_[i]  = 0;
  }
  serial_.begin(baud, SERIAL_8N1);
}

void CRSF::Update() {
  static byte buffer[26];
  static byte * frame_buffer = buffer + 2;
  static byte buffer_index = 0;
  while (serial_.available()) {
    byte rx = serial_.read();
    if (buffer_index == 0 && rx != CSRF_ADDRESS) {
      continue;
    }
    if (buffer_index == 1 && rx != CSRF_LENGTH) {
      continue;
    }
    if (buffer_index == 2 && rx != CSRF_FRAMEID) {
      continue;
    }
    buffer[buffer_index++] = rx;
    if (buffer_index == 26) {
      buffer_index = 0;
      channels_[0]  = ((frame_buffer[1] | frame_buffer[2] << 8) & 0x07FF);
      channels_[1]  = ((frame_buffer[2] >> 3 | frame_buffer[3] << 5) & 0x07FF);
      channels_[2]  = ((frame_buffer[3] >> 6 | frame_buffer[4] << 2 | frame_buffer[5] << 10)  & 0x07FF);
      channels_[3]  = ((frame_buffer[5] >> 1 | frame_buffer[6] << 7) & 0x07FF);
      channels_[4]  = ((frame_buffer[6] >> 4 | frame_buffer[7] << 4) & 0x07FF);
      channels_[5]  = ((frame_buffer[7] >> 7 | frame_buffer[8] << 1 | frame_buffer[9] <<9 ) & 0x07FF);
      channels_[6]  = ((frame_buffer[9] >> 2 | frame_buffer[10] << 6) & 0x07FF);
      channels_[7]  = ((frame_buffer[10] >> 5 | frame_buffer[11] << 3) & 0x07FF);
      channels_[8]  = ((frame_buffer[12] | frame_buffer[13] << 8) & 0x07FF);
      channels_[9]  = ((frame_buffer[13] >> 3 | frame_buffer[14] << 5) & 0x07FF);
      channels_[10] = ((frame_buffer[14] >> 6 | frame_buffer[15] << 2 | frame_buffer[16] << 10) & 0x07FF);
      channels_[11] = ((frame_buffer[16] >> 1 | frame_buffer[17] << 7) & 0x07FF);
      channels_[12] = ((frame_buffer[17] >> 4 | frame_buffer[18] << 4) & 0x07FF);
      channels_[13] = ((frame_buffer[18] >> 7 | frame_buffer[19] << 1 | frame_buffer[20] << 9) & 0x07FF);
      channels_[14] = ((frame_buffer[20] >> 2 | frame_buffer[21] << 6) & 0x07FF);
      channels_[15] = ((frame_buffer[21] >> 5 | frame_buffer[22] << 3) & 0x07FF);
    }
  }
}

int CRSF::FindChannelValue(int channelID) {
  return ((channels_[channelID - 1] / (float) 819) - 1) * 500 + 1500 - 105;
}