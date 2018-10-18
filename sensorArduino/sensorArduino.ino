#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Adafruit_VL6180X.h"

#define TCAADDR 0x70

Adafruit_BNO055 bno = Adafruit_BNO055(55);

Adafruit_VL6180X tof1 = Adafruit_VL6180X();
Adafruit_VL6180X tof2 = Adafruit_VL6180X();
Adafruit_VL6180X tof3 = Adafruit_VL6180X();
Adafruit_VL6180X tof4 = Adafruit_VL6180X();

int ultra1T = 2;
int ultra1E = 3;
int ultra2T = 4;
int ultra2E = 5;
int ultra3T = 6;
int ultra3E = 7;
int ultra4T = 8;
int ultra4E = 9;
int ultra5T = 10;
int ultra5E = 11;
int ultra6T = 12;
int ultra6E = 13;
int ultra7T = A0;
int ultra7E = A1;
int ultra8T = A2;
int ultra8E = A3;

int fireSensor = A4;

void setup() {
  Serial.begin(115200);
  
  pinMode(ultra1T, OUTPUT);
  pinMode(ultra1E, INPUT);
  pinMode(ultra2T, OUTPUT);
  pinMode(ultra2E, INPUT);
  pinMode(ultra3T, OUTPUT);
  pinMode(ultra3E, INPUT);
  pinMode(ultra4T, OUTPUT);
  pinMode(ultra4E, INPUT);
  pinMode(ultra5T, OUTPUT);
  pinMode(ultra5E, INPUT);
  pinMode(ultra6T, OUTPUT);
  pinMode(ultra6E, INPUT);
  pinMode(ultra7T, OUTPUT);
  pinMode(ultra8E, INPUT);
  pinMode(ultra8T, OUTPUT);
  pinMode(ultra8E, INPUT);

  if(!bno.begin()){
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  delay(1000); 
  bno.setExtCrystalUse(true);

  tcaselect(1);
  if(!tof1.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no TOF detected ... Check your wiring!");
    while(1);
  }
  tcaselect(2);
  if(!tof2.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no TOF detected ... Check your wiring!");
    while(1);
  }
  tcaselect(3);
  if(!tof3.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no TOF detected ... Check your wiring!");
    while(1);
  }
  tcaselect(4);
  if(!tof4.begin())
  {
    /* There was a problem detecting the HMC5883 ... check your connections */
    Serial.println("Ooops, no TOF detected ... Check your wiring!");
    while(1);
  }

}

void loop() {
  int ultra1 = readUltrasoinc(ultra1T, ultra1E);
  int ultra2 = readUltrasoinc(ultra2T, ultra2E);
  int ultra3 = readUltrasoinc(ultra3T, ultra3E);
  int ultra4 = readUltrasoinc(ultra4T, ultra4E);
  int ultra5 = readUltrasoinc(ultra5T, ultra5E);
  int ultra6 = readUltrasoinc(ultra6T, ultra6E);
  int ultra7 = readUltrasoinc(ultra7T, ultra7E);
  int ultra8 = readUltrasoinc(ultra8T, ultra8E);
  
  sensors_event_t event; 
  bno.getEvent(&event);
  /* Display the floating point data */
  float bnoX = event.orientation.x;
  float bnoY = event.orientation.y;
  float bnoZ = event.orientation.z;

  tcaselect(1);
  int tof1Range = tof1.readRange();
  tcaselect(2);
  int tof2Range = tof2.readRange();
  tcaselect(3);
  int tof3Range = tof3.readRange();
  tcaselect(4);
  int tof4Range = tof4.readRange();
}

int readUltrasoinc(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distanceCm= duration*0.034/2;
  return(distanceCm);
}

 
void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}
