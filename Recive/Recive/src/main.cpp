#include <Arduino.h>


void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, 17 , 16);


}

void TestCmd(String cmd) {
  Serial1.print(cmd);
  Serial1.print("\r\n");
  Serial.println("Command sent: " + cmd);

}


void loop() {
  TestCmd("Frame Sataya");
  delay(1000);
}
