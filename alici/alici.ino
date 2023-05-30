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
  
  int    deger10;
  int    deger11;
  int    deger12;

  float    deger13;
  float    deger14;
  float    deger15;
  float    deger16;
  float    deger17;

  
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
   
 //  if(Serial.read()=='1'){
    /*
    Serial.println(data.deger1);
    Serial.print("/");
    Serial.println(data.deger2);
    Serial.print("/");
    Serial.println(data.deger3);
    Serial.print("/");*/
                                                      //YER İSTASYONUNDA SPLİT EDİLECEK.
    Serial.print("ivmeX=");
    Serial.println(data.deger4);
    Serial.print("ivmeY");
    Serial.println(data.deger5);
    Serial.print("ivmeZ=");
    Serial.println(data.deger6);
    
    Serial.println("");
    
    Serial.print("GyroX=");
    Serial.println(data.deger7);
    Serial.print("GyroY=");
    Serial.println(data.deger8);
    Serial.print("GyroZ=");
    Serial.println(data.deger9);

    Serial.println("");
/*
    Serial.print("Uydu Sayısı=");
    Serial.println(data.deger10);
    Serial.print("Enlem=");
    Serial.println(data.deger11);
    Serial.print("Boylam=");
    Serial.println(data.deger12);

    Serial.println("");
    */
    Serial.print("Sıcaklık=");
    Serial.println(data.deger13);
    Serial.print("Basınç=");
    Serial.println(data.deger14);
    Serial.print("Rakım=");
    Serial.println(data.deger15);
    Serial.print("Deniz Seviyesi Basınç=");
    Serial.println(data.deger16);
    Serial.print("Gerçek Rakım=");
    Serial.println(data.deger17);

    Serial.println("");
     Serial.println("************************************************************************************");
    rsc.close();
 // }
 delay(500);
  }
}
