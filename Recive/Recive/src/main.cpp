#include <Arduino.h>

int xPin = 34;
int yPin = 35;
int swPin = 25;

void setup() {
  Serial.begin(115200);
  pinMode(swPin, INPUT_PULLUP);
}


void loop() {
  int xRaw = analogRead(xPin);
  int yRaw = analogRead(yPin);

  int xVal = map(xRaw, 0, 4095, 0, 255);
  int yVal = map(yRaw, 0, 4095, 0, 255);

  bool pressed = digitalRead(swPin) == LOW;
  Serial.print("X : ");
  Serial.print(xVal);
  Serial.print(" |  Y : ");
  Serial.print(yVal);
  Serial.print(" |  Pressed : ");
  Serial.println(pressed ? "YES" : "NO");
  delay(50);
}