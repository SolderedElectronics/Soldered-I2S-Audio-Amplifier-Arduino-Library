#include "Soldered_I2S_Audio_Amplifier.h"
#include "WiFi.h"

// Declare GPIOs used
#define I2S_DOUT 25
#define I2S_BCLK 27
#define I2S_LRCLK 26

// Network credentials
const char* SSID = "";
const char* PASSWORD = "";

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

    // Connect to existing WiFi network
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(1000);
    } 

    // Set connected pins
    audio.setPinout(I2S_BCLK, I2S_LRCLK, I2S_DOUT);

    // Set volume, default 0 ... 21
    audio.setVolume(10); 

    // Connect to online audio URL and start streaming
    audio.connecttohost("http://stream.antennethueringen.de/live/aac-64/stream.antennethueringen.de/");
}

void loop()
{
    // audio.loop() must be called constantly
    audio.loop();

    // Prevent distortion
    vTaskDelay(1);
}
