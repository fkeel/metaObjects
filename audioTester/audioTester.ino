#include <SPI.h>
#include <Wire.h>
#include <Audio.h>
#include <SerialFlash.h>

// from: https://forum.pjrc.com/threads/33328-Prop-Shield-Beta-Test?p=99236&viewfull=1#post99236
// modified by Michael Meissner

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=180,469
AudioOutputAnalog        dac1;           //xy=380,468
AudioConnection          patchCord1(sine1, dac1);
// GUItool: end automatically generated code

int freq = 300;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Setting up");
  pinMode(5, OUTPUT);
  digitalWrite(5, 1);    // Enable Amplified.
  AudioMemory(12);
  sine1.amplitude(0.5);
  sine1.frequency(freq);
  Serial.println("Send + to increase freq, - to decrease freq, a to turn off amp, A to turn on amp, or num for freq.");
}

void loop(){

  
}

