#include<Arduino.h>
#include<HardwareSerial.h>

const int M1RPWM = 5;
const int M1LPWM = 6;
const int M1R_EN = 7;
const int M1L_EN = 8;

const int M2RPWM = 10;
const int M2LPWM = 9;
const int M2R_EN = 4;
const int M2L_EN = 3;

const int Red = 13;
const int Green = 11;
const int Blue = 12;

void setup() {
  Serial.begin(115200); 

  pinMode(M1RPWM, OUTPUT);
  pinMode(M1LPWM, OUTPUT);
  pinMode(M1R_EN, OUTPUT);
  pinMode(M1L_EN, OUTPUT);
  pinMode(M2RPWM, OUTPUT);
  pinMode(M2LPWM, OUTPUT);
  pinMode(M2R_EN, OUTPUT);
  pinMode(M2L_EN, OUTPUT);

  pinMode(Red, OUTPUT);
  pinMode(Green, OUTPUT);
  pinMode(Blue, OUTPUT);

  digitalWrite(M1R_EN, HIGH);
  digitalWrite(M1L_EN, HIGH);
  digitalWrite(M2R_EN, HIGH);
  digitalWrite(M2L_EN, HIGH);
}


void Forward() {
  digitalWrite(Green, HIGH);
  digitalWrite(Red, LOW);
  digitalWrite(Blue, LOW);
  analogWrite(M1RPWM, 255);
  analogWrite(M1LPWM, 0);
  analogWrite(M2RPWM, 255);
  analogWrite(M2LPWM, 0);
}

void Backward() {
  digitalWrite(Green, LOW);
  digitalWrite(Red, LOW);
  digitalWrite(Blue, HIGH);
  analogWrite(M1RPWM, 0);
  analogWrite(M1LPWM, 255);
  analogWrite(M2RPWM, 0);
  analogWrite(M2LPWM, 255);
}

void Stop() {
  digitalWrite(Green, LOW);
  digitalWrite(Red, HIGH);
  digitalWrite(Blue, LOW);
  analogWrite(M1RPWM, 0);
  analogWrite(M1LPWM, 0);
  analogWrite(M2RPWM, 0);
  analogWrite(M2LPWM, 0);
}

void loop() {
  
  if (Serial.available()) {
    char cmd = Serial.read();
    switch (cmd) {
      case '1':
        Forward();
        break;
      case '2':
        Backward();
        break;
      case '0':
        Stop();
        break;
    }
  }else{
  }
  
}
