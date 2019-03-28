/*
tes sensor Konduktivitas / TDS / Kadar Garam 
depoinovasi.com
*/

/*
wiring:
terminal 5V -> 5V arduino
terminal output ->  A0 arduino
terminal GND -> GND arduino
*/

#define analogInPin  A1  // Analog input pin 

//variable
int sensorValue; //adc value
float outputValueConductivity; //conductivity value
float outputValueTDS; //TDS value

void setup() {
  //initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  //read the analog in value:
  sensorValue = analogRead(analogInPin);

  //Mathematical Conversion from ADC to conductivity (uSiemens)
  //rumus berdasarkan datasheet
  //outputValueConductivity = (0.2142*sensorValue)+494.93;
  
  //Mathematical Conversion from ADC to TDS (ppm)
  //rumus berdasarkan datasheet
  outputValueTDS = (0.3417*sensorValue)+281.08;
  
  //print the results to the serial monitor:
  //Serial.print("sensor ADC = ");
  //Serial.print(sensorValue);
  //Serial.print("  conductivity (uSiemens)= ");
  //Serial.print(outputValueConductivity);
  Serial.print("TDS(ppm)= ");
  Serial.println(outputValueTDS);

  delay(500);
}
