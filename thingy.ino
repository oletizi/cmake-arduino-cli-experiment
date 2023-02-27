#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include "src/loop.h"
#include "src/thingy_audio_white_noise.h"
thingy::WhiteNoise    waveform1;
//AudioSynthWaveform    waveform1;
AudioOutputI2S        i2s1;
AudioConnection       patchCord1(waveform1, 0, i2s1, 0);
AudioConnection       patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000  audioShield;

void setup() {
    Serial.begin(9600);
    AudioMemory(10);
    audioShield.enable();
    audioShield.volume(0.45);

    //waveform1.pulseWidth(0.5);
    //waveform1.begin(0.4, 220, WAVEFORM_PULSE);
    theloop::setup();
}

void loop() {
    theloop::loop();
}