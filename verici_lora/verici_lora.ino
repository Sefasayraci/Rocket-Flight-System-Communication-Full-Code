/// VERİCİ

#include "LoRa_E22.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
LoRa_E22 E22(&mySerial);
#define M0 7
#define M1 6
struct veriler {
  int    deger1;
  int    deger2;
  int    deger3;
} data;

void setup() {
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);

  Serial.begin(9600);
  E22.begin();
  delay(500);
}

void loop() {
  data.deger1 = 12;
  data.deger2 = 34;
  data.deger3 = 56;


  ResponseStatus rs = E22.sendFixedMessage(0, 0, 23, &data, sizeof(veriler));
  Serial.println(rs.getResponseDescription());

  delay(2000);
}
