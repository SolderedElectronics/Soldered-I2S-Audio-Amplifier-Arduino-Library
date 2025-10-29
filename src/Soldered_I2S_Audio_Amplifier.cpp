#include "Soldered_I2S_Audio_Amplifier.h"

/*
 * @brief Create I2SAudio object
 *
 * @param i2sPort I2S port number (default: I2S_NUM_0)
*/
I2SAudio::I2SAudio(uint8_t i2sPort) : Audio(i2sPort) 
{

}