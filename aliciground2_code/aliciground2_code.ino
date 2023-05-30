// ALICI

#include "LoRa_E22.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // Arduino RX <-- e22 TX, Arduino TX --> e22 RX
LoRa_E22 E22(&mySerial);
#define M0 7
#define M1 6
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
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
  Serial.begin(9600);
  E22.begin();
  delay(500);
}
void loop() {

  while (E22.available()  > 1) {

    // Gelen mesaj okunuyor
    ResponseStructContainer rsc = E22.receiveMessage(sizeof(veriler));
    struct veriler data = *(veriler*) rsc.data;
   // Serial.println("Gelen Messaj: ");
   
   if(Serial.read()=='1'){
    /*
    Serial.println(data.deger1);
    Serial.print("/");
    Serial.println(data.deger2);
    Serial.print("/");
    Serial.println(data.deger3);
    Serial.print("/");*/

    Serial.print(data.deger4);
    Serial.print("/");
    Serial.print(data.deger5);
    Serial.print("/");
    Serial.print(data.deger6);
    Serial.print("/");

    Serial.print(data.deger7);
    Serial.print("/");
    Serial.print(data.deger8);
    Serial.print("/");
    Serial.println(data.deger9);

 
    rsc.close();
  }
  }
}
