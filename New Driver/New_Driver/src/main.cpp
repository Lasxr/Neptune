#include <Arduino.h>

// Motor 1
const int M1L = 27;
const int M1R = 26;
const int M1L_Speed = 14;
const int M1R_Speed = 25;
// Motor 2
const int M2L = 32;
const int M2R = 33;
const int M2L_Speed = 5;
const int M2R_Speed = 4;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 17, 16);

  // M1
  pinMode(M1L, OUTPUT); 
  pinMode(M1R, OUTPUT);
  pinMode(M1L_Speed, OUTPUT);
  pinMode(M1R_Speed, OUTPUT);
  digitalWrite(M1L, HIGH);
  digitalWrite(M1R, HIGH);
  ledcAttachPin(M1L_Speed, 1);
  ledcAttachPin(M1R_Speed, 2);
  ledcSetup(1, 1000, 8);
  ledcSetup(2, 1000, 8);

  // M2
  pinMode(M2L, OUTPUT);
  pinMode(M2R, OUTPUT);
  pinMode(M2L_Speed, OUTPUT);
  pinMode(M2R_Speed, OUTPUT);
  digitalWrite(M2L, HIGH);
  digitalWrite(M2R, HIGH);
  ledcAttachPin(M2L_Speed, 3);
  ledcAttachPin(M2R_Speed, 4);
  ledcSetup(3, 1000, 8);
  ledcSetup(4, 1000, 8);


}

void Forward(int speed) {
  Serial.println("Forward");
  ledcWrite(1, speed);
  ledcWrite(2, 0);
  ledcWrite(3, speed);
  ledcWrite(4, 0);
}

void Backward(int speed) {
  Serial.println("Backward");
  ledcWrite(1, 0);
  ledcWrite(2, speed);
  ledcWrite(3, 0);
  ledcWrite(4, speed);
}

void Stop() {
  Serial.println("Stop");
  ledcWrite(1, 0);
  ledcWrite(2, 0);
  ledcWrite(3, 0);
  ledcWrite(4, 0);
}

void loop() {
  if (Serial1.available()) {
    char cmd = Serial1.read();
    switch (cmd) {
      case '1':
        Forward(125);
        break;
      case '2':
        Backward(125);
        break;
      case '0':
        Stop();
        break;
    }
  }else{
  }
  
}


