#include <Arduino.h>
#include <ESP32Servo.h>



Servo myServo;

// Motor 1
const int M1L = 27;
const int M1R = 26;
const int M1L_Speed = 25;
const int M1R_Speed = 14;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 17, 16);

  myServo.attach(13);

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

}

void Forward(int speed) {
  Serial.println("Forward");
  ledcWrite(1, speed);
  ledcWrite(2, 0);

}

void Backward(int speed) {
  Serial.println("Backward");
  ledcWrite(1, 0);
  ledcWrite(2, speed);

}

void Stop() {
  Serial.println("Stop");
  ledcWrite(1, 0);
  ledcWrite(2, 0);

}

void RxCmd(){
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

void loop() {
  if (Serial.available()) {
    int angle = Serial.parseInt();
    if (angle >= 0 && angle <= 180) {
      myServo.write(angle);
      Serial.print("Rotated to ");
      Serial.println(angle);
    } else {
      Serial.println("Invalid angle. Use 0–180.");
    }
  }
}
