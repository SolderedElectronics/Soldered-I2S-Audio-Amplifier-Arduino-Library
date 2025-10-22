#ifndef __I2S_AUDIO_AMPLIFIER_H
#define __I2S_AUDIO_AMPLIFIER_H

#include "Arduino.h"
#include "libs/ESP32-audioI2S-master/src/Audio.h"

class I2SAudio : public Audio
{
  public:
    I2SAudio(uint8_t i2sPort = I2S_NUM_0);
};

#endif