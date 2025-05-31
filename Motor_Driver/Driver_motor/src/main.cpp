#include <Arduino.h>

// Motor Digital
int M1L = 5;
int M1R = 6;
int M2L = 10;
int M2R = 11;

// PWM Motor
int MPWM1L = 3;
int MPWM1R = 4;
int MPWM2L = 8;
int MPWM2R = 9;

char key = '0';

int LED = 13; 

void setup(){
  Serial.begin(9600);
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

  Serial.println("Setup complete!");
}

void loop(){
  while(Serial.available() > 0){
    key = Serial.read();
    Serial.print("Key: ");
    Serial.println(key);
    
    switch(key){
      case '1':
        digitalWrite(M1L, HIGH);
        break;
      case '2':
        digitalWrite(M1L, LOW);
        digitalWrite(M1R, HIGH);
        break;
      case '3':
        digitalWrite(M2L, HIGH);
        digitalWrite(M2R, LOW);
        break;
      case '4':
        digitalWrite(M2L, LOW);
        digitalWrite(M2R, HIGH);
        break;
      case '5':
        digitalWrite(LED, HIGH);
        break;
      case '6':
        digitalWrite(LED, LOW);
        break;
      default:
        Serial.println("Invalid key!");
    }
  }
}