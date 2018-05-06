

#include <NXPMotionSense.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Audio.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Bounce.h>
NXPMotionSense imu;
NXPSensorFusion filter;

AudioSynthWaveformSine   sine1;          //xy=180,469
AudioOutputAnalog        dac1;           //xy=380,468
AudioConnection          patchCord1(sine1, dac1);
int freq = 300;
int currentStep = 0;
//beep without delay
const int ledPin =  13;      // the number of the LED pin
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
long interval = 1000;           // interval at which to blink (milliseconds)
unsigned long startPulse = 0;


float previousValue;
float currentValue;

void setup() {
  // Serial.begin(9600);
  imu.begin();
  filter.begin(100);

  AudioMemory(12);
  dac1.analogReference(EXTERNAL); // much louder!
  delay(50);             // time for DAC voltage stable
  pinMode(5, OUTPUT);
  digitalWrite(5, HIGH); // turn on the amplifier
  delay(10);             // allow time to wake up            // allow time to wake up

  sine1.amplitude(0.05);
  sine1.frequency(freq);

  pinMode(ledPin, OUTPUT);

}

void loop() {
  float ax, ay, az;
  float gx, gy, gz;
  float mx, my, mz;
  float roll, pitch, heading;

  if (imu.available()) {
    // Read the motion sensors
    imu.readMotionSensor(ax, ay, az, gx, gy, gz, mx, my, mz);

    // Update the SensorFusion filter
    filter.update(gx, gy, gz, ax, ay, az, mx, my, mz);

    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();
    // Serial.print("Orientation: ");
    //  Serial.print(heading);
    //  Serial.print(" ");
    //  Serial.print(pitch);
    //  Serial.print(" ");
    //  Serial.println(roll);

    //  sine1.frequency(heading);

  }


  if (  thresholdReached(roll, 2)) {
    //  startPulse = millis();
    //   Serial.println("Threshold Reached!");
    //  Serial.println(currentStep);
  }
  currentValue = roll;
  float f = abs(previousValue - currentValue);
  Serial.println(f);
  sine1.frequency(f*80);
 if(f<0.1){
//  sine1.amplitude(0);
 } else {
//  sine1.amplitude(0.1);
 }
  previousValue = currentValue;

  //  pulse(250, 0, 2, startPulse); //frquency, offTime, onTime, currenttime
  delay(30);
}

