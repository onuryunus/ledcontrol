/*
  Eae Project - Adaptive Led Control with using External Interrupt

  This project was developed for EAE Tech Company. This project provides LED status change with long and short press to button.

  The circuit:
  * Button ( Pull-up state )
  * LED

  Date : 02/07/2018
  Author : Yunus Önür
  https://github.com/onuryunus
  
*/


#include <EEPROM.h>
long recyclestartTime = 0; // Butona basıldıgındaki zaman parametresi.
long recyclestopTime = 0; // Butondan elin cekildigi andaki zaman parametresi.
long cycletime = 0; // Butona ne kadar basıldıgını ifade edecek parametre.
long interruptPin = 2; // Kesme yaratacak butonumuzun pini.
int ledPin = 10; // Kırpmaları değişecek olan ledimizin parametresi.
void setup() 
{
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP); //
  attachInterrupt(digitalPinToInterrupt(interruptPin), starttimer, RISING); // Bu komut ile butona basıldıgı anda ( Yukselen kenarda ) bir kesme yaratıyoruz 
                                                                                // bu kesme starttimer fonksiyonunu ( butona basılma anını yakalayan fonksiyon )cagırmakta. 
} 

void loop()
{
  EEPROM.get(0, recyclestartTime);  //
  EEPROM.get(100, recyclestopTime); // Hafızanın içinden önceki basım ile alakalı veriler işlenmek üzere çekilir.
  cycletime = recyclestartTime - recyclestopTime ; // Butona basılma ve butondan elin çekilme anının farkı ile toplam zaman bulunur.
  
  if (cycletime < 200) // Eğer kısa süreli basım ise ( Proje dosyasında 100 ms saniye olması ön görülmüş fakat bu gerçekleştirilemeyecek kadar düşük bir saniye olduğundan 200 ms tercih edilmiştir.)
  {
    blink1(); // Proje dosyasında kısa süreli basımda gerçekleştirilmesi istenen durumun fonksiyonu.
  }
  else if ( cycletime > 2500 && cycletime < 3500 )  // Proje dosyasında istenildiği üzere uzun basım ( 2.5 saniye ile 3.5 saniye aralığı alınmıştır.)
  {
    blink2(); // Proje dosyasında uzun süreli basımda gerçekleştirilmesi istenen durumun fonksiyonu.
  }
}

void starttimer()
{
  recyclestartTime = millis(); // Fonksiyon başlar başlamaz ( Butona basıldıgı an ) ki zamanı kaydediyoruz.
  EEPROM.put(0, recyclestartTime); // Kaydedilen zamanı EEPROM yardımıyla hafızaya gönderiyoruz. Daha sonra zaman farkını bulabilmek için.
  attachInterrupt(0, stoptimer, FALLING); // Butondan elimizi çektiğimizde ( Düşen kenarda ) stoptimer fonksiyonunu çalıştırıyoruz.
}
void stoptimer()
{
  recyclestopTime = millis(); // Butondan elin çekilme anındaki zaman kaydedilir.
  EEPROM.put(100, recyclestopTime); // EEPROM'un 100 adresine bu zaman parametresi atanır.
  attachInterrupt(0, starttimer, RISING); 
}

void blink1() // Kısa süreli basım halinde gerçekleşecek led kırpma fonksiyonu.
{
  for (int count = 0; count < 2; count++) 
  {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
  }
  for (int count = 0; count < 2; count++) 
  {
    digitalWrite(ledPin, HIGH);
    delay(2000);
    digitalWrite(ledPin, LOW);
    delay(2000);
  }
}
void blink2() // Uzun süreli basım halinde gerçekleşecek led kırpma fonksiyonu.
{
  for (int count = 0; count < 5; count++) 
  {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
  }
  for (int count = 0; count < 5; count++) 
  {
    digitalWrite(ledPin, HIGH);
    delay(2000);
    digitalWrite(ledPin, LOW);
    delay(2000);
  }
}
