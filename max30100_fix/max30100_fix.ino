#include <Arduino.h>
#include <math.h>
#include <Wire.h>

#include "MAX30100.h"

MAX30100* pulseOxymeter;
float temp;
int tempPin = 0;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  //pulseOxymeter = new MAX30100( DEFAULT_OPERATING_MODE, DEFAULT_SAMPLING_RATE, DEFAULT_LED_PULSE_WIDTH, DEFAULT_IR_LED_CURRENT, true, true );
  pulseOxymeter = new MAX30100();
  pinMode(2, OUTPUT);

  //pulseOxymeter->printRegisters();
}

void loop() {
  //return;
  //You have to call update with frequency at least 37Hz. But the closer you call it to 100Hz the better, the filter will work.
  pulseoxymeter_t result = pulseOxymeter->update();
  

  if( result.pulseDetected == true )
  {

    temp = analogRead(tempPin);
    temp = temp * 0.48828125;
    Serial.print(temp);
    Serial.print(",");
    Serial.print(result.heartBPM);
    Serial.print(",");
    //Serial.print("bpm / SpO2:");
    Serial.println(result.SaO2);
   

  }

 

  delay(10);

  //Basic way of determening execution of the loop via oscoliscope
  //digitalWrite( 2, !digitalRead(2) );
}
