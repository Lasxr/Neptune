#include<Arduino.h>
#include <SPI.h> 
#include <LoRa.h>


void setup() {
  Serial.begin(115200); 

  LoRa.setPins(5, 14, 26);    // NSS, RST, DIO0
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }
  //LoRa.setTxPower(10);

  Serial.println("LoRa Receiver Ready");


}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String msg = "";
    while (LoRa.available()) {
      msg += (char)LoRa.read();
    }
    Serial.print("Recived : ");
    Serial.println(msg);
  }
  delay(20);
}