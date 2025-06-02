#include <Arduino.h>
#include <SoftwareSerial.h>


SoftwareSerial mySerial(11, 12); // RX, TX

// ขาเชื่อมต่อกับ BTS7960
const int M1RPWM = 5;
const int M1LPWM = 6;
const int M1R_EN = 7;
const int M1L_EN = 8;

const int M2RPWM = 10;
const int M2LPWM = 9;
const int M2R_EN = 4;
const int M2L_EN = 3;


void setup() {
  Serial.begin(9600);

  pinMode(M1RPWM, OUTPUT);
  pinMode(M1LPWM, OUTPUT);
  pinMode(M1R_EN, OUTPUT);
  pinMode(M1L_EN, OUTPUT);

  pinMode(M2RPWM, OUTPUT);
  pinMode(M2LPWM, OUTPUT);
  pinMode(M2R_EN, OUTPUT);
  pinMode(M2L_EN, OUTPUT);

  // เปิดใช้งานทั้งสองขา
  digitalWrite(M1R_EN, HIGH);
  digitalWrite(M1L_EN, HIGH);
  digitalWrite(M2R_EN, HIGH);
  digitalWrite(M2L_EN, HIGH);
}


void ReciveCmd(){
  if (mySerial.available()) {
    String msg = mySerial.readStringUntil('\n');
    Serial.println("Received: " + msg);
  }
}

void Forward(int time){
  Serial.println("Forward");
  analogWrite(M1RPWM, 255);  // ความเร็ว 0-255
  analogWrite(M1LPWM, 0);
  analogWrite(M2RPWM, 255);  // ความเร็ว 0-255
  analogWrite(M2LPWM, 0);
  delay(time);
}

void Backward(int time){
  Serial.println("Backward");
  analogWrite(M1RPWM, 0);  // ความเร็ว 0-255
  analogWrite(M1LPWM, 255);
  analogWrite(M2RPWM, 0);  // ความเร็ว 0-255
  analogWrite(M2LPWM, 255);
  delay(time);
}

void Stop(int time){
  Serial.println("Stop");
  analogWrite(M1RPWM, 0);  // ความเร็ว 0-255
  analogWrite(M1LPWM, 0);
  analogWrite(M2RPWM, 0);  // ความเร็ว 0-255
  analogWrite(M2LPWM, 0);
  delay(time);
}

void loop() {
  Forward(3000);
  Stop(1000);
  Backward(3000);
  Stop(1000);
}
