#include<Arduino.h>
#include <SPI.h>
#include <LoRa.h>

const int Xpin = 35;
const int Ypin = 33;
const int SWpin = 16;

void setup() {

  pinMode(SWpin, INPUT_PULLUP);

  Serial.begin(115200);

  LoRa.setPins(5, 14, 26);  // NSS, RST, DIO0

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }
  //LoRa.setTxPower(10);

  Serial.println("LoRa Receiver Ready");

}

void loop() {
  int ValX = analogRead(Xpin);
  int ValY = analogRead(Ypin);
  int SWval = digitalRead(SWpin);

  Serial.print("Val X: ");
  Serial.print(ValX);
  Serial.print(" | Val Y: ");
  Serial.print(ValY);
  Serial.print(" | Button: ");
  Serial.println(SWval == LOW ? "Pressed" : "Released"); 

  LoRa.beginPacket();
  LoRa.print("X:");
  LoRa.print(ValX);
  LoRa.print(",Y:");
  LoRa.print(ValY);
  LoRa.print(",SW:");
  LoRa.print(SWval == LOW ? 1 : 0);
  LoRa.endPacket();


  delay(50);
}
