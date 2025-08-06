#include<Arduino.h>
#include <SPI.h> 
#include <LoRa.h>

int On_Board = 2;

unsigned long lastReceiveTime = 0;
unsigned long timeoutDuration = 5000;

int xVal, yVal, swVal;

void setup() {
  Serial.begin(115200);

  pinMode(On_Board, OUTPUT);

  LoRa.setPins(5, 14, 26);    // NSS, RST, DIO0
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    digitalWrite(On_Board, 0);
    while (1);
  }
  //LoRa.setTxPower(10);
  digitalWrite(On_Board, 1);
  Serial.println("LoRa Receiver Ready");


}

void parseData(String data) {
  int xIndex = data.indexOf("X:") + 2;
  int yIndex = data.indexOf("Y:") + 2;
  int swIndex = data.indexOf("SW:") + 3;

  int comma1 = data.indexOf(',');
  int comma2 = data.lastIndexOf(',');

  String xStr = data.substring(xIndex, comma1);
  String yStr = data.substring(yIndex, comma2);
  String swStr = data.substring(swIndex);

  xVal = xStr.toInt();
  yVal = yStr.toInt();
  swVal = swStr.toInt();
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

    parseData(msg);
    Serial.print("X: "); Serial.println(xVal);
    Serial.print("Y: "); Serial.println(yVal);
    Serial.print("SW: "); Serial.println(swVal);

    lastReceiveTime = millis();
  }
  if (millis() - lastReceiveTime > timeoutDuration) {
  xVal = 0;
  yVal = 0;
  swVal = 0;
  digitalWrite(On_Board, LOW);
}
}