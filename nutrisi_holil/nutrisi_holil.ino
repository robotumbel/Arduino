#include "DHT.h" //library sensor yang telah diimportkan
#define DHTPIN A0     //Pin apa yang digunakan
#define DHTTYPE DHT11   // DHT 11

#define tdsport  A1  // Analog input pin 
DHT dht(DHTPIN, DHTTYPE);

int tds; //adc value
float outputValueConductivity; //conductivity value
float outputValueTDS; //TDS value


#define PHport A2            //pH meter Analog output to Arduino Analog Input 0
#define Offset 0.00            //deviation compensate
#define samplingInterval 20
#define printInterval 800
#define ArrayLenth  40    //times of collection
int pHArray[ArrayLenth];   //Store the average value of the sensor feedback
int pHArrayIndex=0;  

void setup() {
  Serial.begin(9600); //baud komunikasi serial
  dht.begin(); //prosedur memulai pembacaan module sensor

}

void loop() {
    float humidity_1 = dht.readHumidity();
  //Pembacaan dalam format celcius (c)
    float celcius_1 = dht.readTemperature();
    tds = analogRead(tdsport);
    outputValueTDS = (0.3417*tds)+281.08;

    int turbisensor = analogRead(A3);// read the input on analog pin 0:
    float turbidity = turbisensor * (5.0 / 1024.0); // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
    Serial.print(turbidity); // print out the value you read:

    static unsigned long samplingTime = millis();
    static unsigned long printTime = millis();
    static float pHValue,voltage;
    if(millis()-samplingTime > samplingInterval)
    {
        pHArray[pHArrayIndex++]=analogRead(PHport);
        if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
        voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
        pHValue = 3.5*voltage+Offset;
        samplingTime=millis();
    }
    if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
    {
          //Serial.print("Voltage:");
          //Serial.print(voltage,2);
          Serial.print(" pH value: ");
          Serial.print(pHValue,2);
          Serial.print(",");
          printTime=millis();
    }

    Serial.print("Kelembaban:");
    Serial.print(humidity_1);
    Serial.print("t,");
    
    //pembacaan nilai pembacaan data suhu
    Serial.print("Suhu :");
    Serial.print(celcius_1); //format derajat celcius
    Serial.print(" 'C, ");

    Serial.print("Tds :");
    Serial.print(outputValueTDS); //format derajat celcius
    Serial.print(" ppm,");

    Serial.print("turbidity :");
    Serial.print(outputValueTDS); //format derajat celcius
    Serial.println(",");

}

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
