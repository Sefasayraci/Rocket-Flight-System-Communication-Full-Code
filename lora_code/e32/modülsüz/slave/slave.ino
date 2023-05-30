//#define E32_TTL_1W // E32 30d modülleri için bunu aktif et
#include "LoRa_E32.h"  // E32 modülleri için bunu aktif et
#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(10, 11);
LoRa_E32 FixajSS(&mySerial);
 
#define M0 7
#define M1 6
 
#define Adres 2   //0--65000 arası bir değer girebilirsiniz. Diğer Modüllerden FARKLI olmalı
#define Kanal 20  //Frekans değeri
//E32 için 0--31 arasında bir sayı giriniz.
//E32 433 için Frekans = 410+kanal değeri
 
struct Signal {
  char sifre[15];
  char konum[15];
  bool btn1;
  byte btn2[10];
  byte btn3[4];
} data;
 
 
void setup() {
  pinMode(M0, OUTPUT);
  pinMode(M1, OUTPUT);
 
  Serial.begin(9600);
  FixajSS.begin();
 
  LoraE32Ayarlar();
 
  digitalWrite(M0, LOW);
  digitalWrite(M1, LOW);
 
  delay(500);
  Serial.println("başlıyoruz.. Fixaj.com");
}
 
void loop() {
  while (FixajSS.available() > 1) {
 
    ResponseStructContainer rsc = FixajSS.receiveMessage(sizeof(Signal));
    struct Signal data = *(Signal*)rsc.data;
    rsc.close();
 
    if (strcmp(data.sifre, "Fixaj.com") == 0) {
      Serial.println("Sifre doğru");
      Serial.print("Konum: ");
      Serial.println(data.konum);
      Serial.print("buton durumu: ");
      Serial.println(data.btn1);
      Serial.print("Kordinat: ");
      Serial.println(*(float*)(data.btn2), 6);
      Serial.print("Büyük sayı: ");
      Serial.println(*(int*)(data.btn3));
    }
  }
}
 
void LoraE32Ayarlar() {
  digitalWrite(M0, HIGH);
  digitalWrite(M1, HIGH);
 
  ResponseStructContainer c;
  c = FixajSS.getConfiguration();
  Configuration configuration = *(Configuration*)c.data;
 
  //DEĞİŞEBİLEN AYARLAR
  // Üstte #define kısmında ayarlayınız
  configuration.ADDL = lowByte(Adres);
  configuration.ADDH = highByte(Adres);
  configuration.CHAN = Kanal;
 
  //SEÇENEKLİ AYARLAR
  configuration.SPED.airDataRate = AIR_DATA_RATE_010_24;  //Veri Gönderim Hızı 2,4 varsayılan
  //configuration.SPED.airDataRate = AIR_DATA_RATE_000_03;  //Veri Gönderim Hızı 0,3 En uzak Mesafe
  //configuration.SPED.airDataRate = AIR_DATA_RATE_101_192; //Veri Gönderim Hızı 19,2 En Hızlı
 
  configuration.OPTION.transmissionPower = POWER_20;  //Geönderim Gücü max Varsayılan
  //configuration.OPTION.transmissionPower = POWER_10;  //Geönderim Gücü min
  //configuration.OPTION.transmissionPower = POWER_30; // E32 30d modülleri için bunu aktif et
 
  //GELİŞMİŞ AYARLAR
  configuration.SPED.uartBaudRate = UART_BPS_9600;
  configuration.SPED.uartParity = MODE_00_8N1;
  configuration.OPTION.fec = FEC_0_OFF;
  //configuration.OPTION.fec = FEC_1_ON;
  configuration.OPTION.fixedTransmission = FT_FIXED_TRANSMISSION;
  //configuration.OPTION.fixedTransmission = FT_TRANSPARENT_TRANSMISSION;
  configuration.OPTION.wirelessWakeupTime = WAKE_UP_250;
  configuration.OPTION.ioDriveMode = IO_D_MODE_PUSH_PULLS_PULL_UPS;
 
  // Ayarları KAYDET ve SAKLA
  ResponseStatus rs = FixajSS.setConfiguration(configuration, WRITE_CFG_PWR_DWN_SAVE);
  c.close();
}
