/**
 **************************************************
 *
 * @file        Audio_Over_SD_Card.ino
 *
 * @brief       Example that shows how to play audio file 
 *              from a WAV file stored on SD card over I2S. 
 *              Supported file types are: WAV, MP3, M4A.
 *
 *              
 *
 *
 *
 * @link        solde.red/333355
 *              Stereo I2S Digital Audio Amplifier (SKU: 333355)
 *
 * @authors     Dino Ragač
 *
 **************************************************
 */

#include "Soldered_I2S_Audio_Amplifier.h"

// Declare amplifier GPIOs used
#define I2S_DOUT 25
#define I2S_BCLK 27
#define I2S_LRCLK 26

// Declare SD card SPI pins
#define SD_CS          5
#define SPI_MOSI      23
#define SPI_MISO      19
#define SPI_SCK       18

// Create an instance of audio player object
I2SAudio audio;

// Audio callback function, gives full information of current audio source (optional but good to have)
void my_audio_info(I2SAudio::msg_t m) 
{
  Serial.printf("%s: %s\n", m.s, m.msg);
}

void setup() 
{
  Serial.begin(115200);
  // Declare callback function
  I2SAudio::audio_info_callback = my_audio_info;

  // Manually control the SPI chip select, pulled high to deselect the bus 
  pinMode(SD_CS, OUTPUT);
  digitalWrite(SD_CS, HIGH);

  // Begin SPI communication with set frequency at 1MHz
  SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
  SPI.setFrequency(1000000);

  // Initialize the SD card over SPI bus
  SD.begin(SD_CS);

  // Set audio amplifier pins to output I2S digital audio
  audio.setPinout(I2S_BCLK, I2S_LRCLK, I2S_DOUT);

  // Set volume, default 0 ... 21
  audio.setVolume(5); 

  // Below are shown functions for adjusting the EQ and RIGHT/LEFT channel balance (volume)
  //
  // IIR filter to adjust bass and treble (3 band equalizer)
  // setTone(0, 0, 0) is default setting, values can be between -40 ... +6 (dB)
  //
  //    NOTE: This will cause a slight clicking sound when adjusting the EQ.
  //          When EQ is adjusted the filter is cleared and played,
  //          mixed in the audio data frame.
  //
  // audio.setTone(2, -10, 2); 

  // setBalance(); values between -16 ... 16 mute the left or right channel
  //  Mutes right channel
  //
  // audio.setBalance(16);

  // Open stored file from SD card in correct format and pass to audio buffer
  audio.connecttoFS(SD, "example.wav");
}

void loop() 
{
  // audio.loop() must be called constantly
  audio.loop();

  // Prevent distortion
  vTaskDelay(1);
}
