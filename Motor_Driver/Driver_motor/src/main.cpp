#include<Arduino.h>
#include<HardwareSerial.h>

#include <Servo.h>

Servo myServo;

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

  myServo.attach(9);

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

void loop() {



}