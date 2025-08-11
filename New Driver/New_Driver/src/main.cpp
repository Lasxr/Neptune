#include<Arduino.h>
#include <SPI.h> 
#include <LoRa.h>

int On_Board = 2;

int M1_L = 27;
int M1_R = 25;

int L_EN = 15;
int R_EN = 4;

int M2_L = 13;
int M2_R = 12;

unsigned long lastReceiveTime = 0;
unsigned long timeoutDuration = 2000;

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
  LoRa.setTxPower(10);



  pinMode(M1_L, OUTPUT);
  pinMode(M1_R, OUTPUT);
  pinMode(M2_L, OUTPUT);
  pinMode(M2_R, OUTPUT);
  pinMode(L_EN, OUTPUT);
  pinMode(R_EN, OUTPUT);

  digitalWrite(L_EN, 1);
  digitalWrite(R_EN, 1);

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


void Motor_Run(int Speed_L, int Speed_R){
  
  if(Speed_L > 0){
    Serial.println("MotorL_F");
    analogWrite(M1_L, Speed_L);
    analogWrite(M1_R, 0);

  }else if (Speed_L < 0){
    Serial.println("MotorL_B");
    analogWrite(M1_L, 0);
    analogWrite(M1_R, abs(Speed_L));

  }

  if(Speed_R > 0){
    Serial.println("MotorR_F");
    analogWrite(M2_L, Speed_R);
    analogWrite(M2_R, 0);

  }else if (Speed_R < 0){
    Serial.println("MotorR_B");
    analogWrite(M2_L, 0);
    analogWrite(M2_R, abs(Speed_R));

  }

}



void  loop() {
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

    int Con_R = yVal - xVal;
    int Con_L = yVal + xVal;
    
    Con_L = constrain(Con_L, -125, 125);
    Con_R = constrain(Con_R, -125, 125);
    
    Motor_Run(Con_L, Con_R);

    lastReceiveTime = millis();
  }
  delay(20);
  if (millis() - lastReceiveTime > timeoutDuration) {
  xVal = 0;
  yVal = 0;
  swVal = 0;
  digitalWrite(On_Board, LOW);

  ESP.restart();
  }
}