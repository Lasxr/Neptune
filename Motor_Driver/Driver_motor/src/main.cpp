#include <Arduino.h>
#include <SoftwareSerial.h>


SoftwareSerial mySerial(11, 12); // RX, TX

// Motor Digital
int M2L = 3;
int M2R = 4;
int M1L = 7;
int M1R = 8;

// PWM Motor
int MPWM1L = 6;
int MPWM1R = 5;
int MPWM2L = 9;
int MPWM2R = 10;

uint8_t SM1L = 125; 
uint8_t SM1R = 125; 
uint8_t SM2L = 125; 
uint8_t SM2R = 125; 

int LED = 13; 

void setup(){
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Program start!");
  // Motor
  pinMode(M1L, OUTPUT);
  pinMode(M1R, OUTPUT);
  pinMode(M2L, OUTPUT);
  pinMode(M2R, OUTPUT);
  // PWM
  pinMode(MPWM1L, OUTPUT);
  pinMode(MPWM1R, OUTPUT);
  pinMode(MPWM2L, OUTPUT);
  pinMode(MPWM2R, OUTPUT);

  pinMode(LED, OUTPUT);

  
  analogWrite(MPWM1L, SM1L);
  analogWrite(MPWM1R, SM1R);
  analogWrite(MPWM2L, SM2L);
  analogWrite(MPWM2R, SM2R);
  
  Serial.println("Setup complete!");
}

void Forward(int Delay){
  Serial.println("Forward");
  digitalWrite(M1L, HIGH);
  digitalWrite(M1R, LOW);
  digitalWrite(M2L, HIGH);
  digitalWrite(M2R, LOW);
  delay(Delay);
}

void Backward(int Delay){
  Serial.println("Backward");
  digitalWrite(M1L, LOW);
  digitalWrite(M1R, HIGH);
  digitalWrite(M2L, LOW);
  digitalWrite(M2R, HIGH);
  delay(Delay);
}

void ReciveCmd(){
  if (mySerial.available()) {
    String msg = mySerial.readStringUntil('\n');
    Serial.println("Received: " + msg);
  }
}

void loop(){
  Forward(1000);
  Backward(1000);
}