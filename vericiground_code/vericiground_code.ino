/// VERİCİ
#include <MPU6050.h>
#include <Wire.h>

#include "LoRa_E22.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
LoRa_E22 E22(&mySerial);

#define M0 7
#define M1 6

MPU6050 sensor;


int ivmeX , ivmeY , ivmeZ , GyroX , GyroY , GyroZ;
struct veriler {
  int    deger1;
  int    deger2;
  int    deger3;
  
  int    deger4;
  int    deger5;
  int    deger6;

  int    deger7;
  int    deger8;
  int    deger9;
  
} data;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  sensor.initialize();
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);

  //Serial.begin(9600);
  E22.begin();
  delay(500);
}

void loop() {
  
  sensor.getMotion6(&ivmeX, &ivmeY, &ivmeZ, &GyroX, &GyroY, &GyroZ);
  
  data.deger1 = 12;
  data.deger2 = 34;
  data.deger3 = 56;
  
  data.deger4 = ivmeX;
  data.deger5 = ivmeY;
  data.deger6 = ivmeZ;
  
  data.deger7 = GyroX;
  data.deger8 = GyroY;
  data.deger9 = GyroZ;
/*
    Serial.print(ivmeX);//ivme X
    Serial.print("/");
    Serial.print(ivmeY);//ivme y
    Serial.print("/");
    Serial.print(ivmeZ);//ivme z
    Serial.print("/");
    Serial.print(GyroX);//gyro x
    Serial.print("/");
    Serial.print(GyroY);//gyro y
    Serial.print("/");
    Serial.println(GyroZ);//gyro z
*/

  ResponseStatus rs = E22.sendFixedMessage(0, 0, 23, &data, sizeof(veriler));
  Serial.println(rs.getResponseDescription());

  delay(200);
}
