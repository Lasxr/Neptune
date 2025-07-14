#include <SPI.h>
#include <LoRa.h>

const int analogPin = 34;

void setup() {
  Serial.begin(115200);
  LoRa.setPins(5, 14, 26);  // NSS, RST, DIO0
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }
  Serial.println("LoRa Sender Ready");
}

void loop() {
  int sensorVal = analogRead(analogPin);           // ได้ค่า 0–4095
  String data = String(sensorVal);                 // ส่งเป็นข้อความ
  LoRa.beginPacket();
  LoRa.print(data);
  LoRa.endPacket();

  Serial.println("analog: " + data);
  delay(10);
}
