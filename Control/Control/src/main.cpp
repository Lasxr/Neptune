#include<Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 

#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const int Xpin = 35;
const int Ypin = 33;
const int SWpin = 16;

int DeadZone = 300;
int Center = 2800;

int smoothX = 0;
int smoothY = 0;

int On_Board = 2;
void setup() {

  pinMode(SWpin, INPUT_PULLUP);
  pinMode(On_Board, OUTPUT);

  Serial.begin(115200);

  LoRa.setPins(5, 14, 26);  // NSS, RST, DIO0

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }
  //LoRa.setTxPower(10);
  
  Serial.println("LoRa Receiver Ready");
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Start Program Control");
  display.println(" ");
  display.println("        Ready!");
  display.display();

}

void JoySent(int Speed){

  int RawX = analogRead(Xpin);
  int RawY = analogRead(Ypin);
  int SWval = digitalRead(SWpin);


  int joyX = RawX - Center;
  int joyY = RawY - Center;


  if (abs(joyX) < DeadZone) joyX = 0;
  if (abs(joyY) < DeadZone) joyY = 0;
  
  joyX = constrain(joyX, -1295, 1295);
  joyY = constrain(joyY, -1295, 1295);

  smoothX = 0.3 * smoothX + 0.2 * joyX;
  smoothY = 0.3 * smoothY + 0.2 * joyY;
  
  int ValX = map(smoothX, -323, 323, -Speed, Speed);
  int ValY = map(smoothY, -323, 323, -Speed, Speed);
  
  ValX = constrain(ValX, -Speed , Speed);
  ValY = constrain(ValY, -Speed , Speed);

  ValX = -ValX;
  ValY = -ValY;

  Serial.print("Val X: ");
  Serial.print(ValX);
  Serial.print(" | Val Y: ");
  Serial.print(ValY);
  Serial.print(" | Button: ");
  Serial.println(SWval == LOW ? "Pressed" : "Released"); 

  LoRa.beginPacket();
  LoRa.print("X:");
  LoRa.print(ValX);
  LoRa.print(",Y:");
  LoRa.print(ValY);
  LoRa.print(",SW:");
  LoRa.print(SWval == LOW ? 1 : 0);
  LoRa.endPacket();

  display.fillRect(0, 40, 128, 24, SSD1306_BLACK); // ลบเฉพาะส่วนแสดงค่าเก่า
  display.setCursor(0, 40);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.print("      ");
  display.print(ValX);
  display.print(" | ");
  display.print(ValY);
  display.print(" | ");
  display.print(SWval == LOW ? 1 : 0);
  display.display();

  if (ValX == 125 || ValX == -125 || ValY == 125 || ValY == -125) {
  display.setCursor(0, 54);
  display.print("      Max Speed !");
  display.display();
  digitalWrite(On_Board, 1);
}else{
  digitalWrite(On_Board, 0);
}
}


void loop() {
  JoySent(125);   //ถ้ามึงออกเกิน 200 Driver มึงกลับสวรรค์แน่
  delay(50);
}
