#include <Arduino.h>

// ขา BTS7960
const int M1RPWM = 5;
const int M1LPWM = 6;
const int M1R_EN = 7;
const int M1L_EN = 8;

const int M2RPWM = 10;
const int M2LPWM = 9;
const int M2R_EN = 4;
const int M2L_EN = 3;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 16, 17); // RX=16, TX=17

  // ตั้งค่าขา BTS7960
  pinMode(M1RPWM, OUTPUT);
  pinMode(M1LPWM, OUTPUT);
  pinMode(M1R_EN, OUTPUT);
  pinMode(M1L_EN, OUTPUT);
  pinMode(M2RPWM, OUTPUT);
  pinMode(M2LPWM, OUTPUT);
  pinMode(M2R_EN, OUTPUT);
  pinMode(M2L_EN, OUTPUT);

  digitalWrite(M1R_EN, HIGH);
  digitalWrite(M1L_EN, HIGH);
  digitalWrite(M2R_EN, HIGH);
  digitalWrite(M2L_EN, HIGH);

  Serial.println("🚀 Ready to receive commands");
}

void moveForward() {
  analogWrite(M1RPWM, 255);
  analogWrite(M1LPWM, 0);
  analogWrite(M2RPWM, 255);
  analogWrite(M2LPWM, 0);
  Serial.println("⬆️ Forward");
}

void moveBackward() {
  analogWrite(M1RPWM, 0);
  analogWrite(M1LPWM, 255);
  analogWrite(M2RPWM, 0);
  analogWrite(M2LPWM, 255);
  Serial.println("⬇️ Backward");
}

void stopMotors() {
  analogWrite(M1RPWM, 0);
  analogWrite(M1LPWM, 0);
  analogWrite(M2RPWM, 0);
  analogWrite(M2LPWM, 0);
  Serial.println("🛑 Stop");
}

void loop() {
  if (Serial2.available()) {
    char cmd = Serial2.read();
    Serial.print("📩 Received: ");
    Serial.println(cmd);

    switch (cmd) {
      case '1':
        moveForward();
        break;
      case '2':
        moveBackward();
        break;
      case '0':
        stopMotors();
        break;
      default:
        Serial.println("❓ Unknown command");
    }
  }
}
