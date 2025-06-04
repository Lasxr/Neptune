#include <Arduino.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;


bool isConnected = false;

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200, SERIAL_8N1, 17 , 16); // RX-16 TX-17
  SerialBT.begin("Neptune Inwza");
  Serial.println("Bluetooth ready");
}

void TestCmd(String cmd) {
  Serial1.print(cmd);
  Serial1.print("\r\n");
  Serial.println("Command sent: " + cmd);

}

void BTReceive() {
  while (SerialBT.available()) {
    char BTcmd = SerialBT.read();
    Serial.println("Received: " + String(BTcmd));
    Serial1.write(BTcmd);
  }
}


void loop() {
  if (SerialBT.hasClient()) {
    if (!isConnected) {
      Serial.println("Bluetooth connected");
      isConnected = true;
    }
    BTReceive();
  } else {
    if (isConnected) {
      Serial.println("Bluetooth disconnected");
      isConnected = false;
    }
  }
  delay(100);
}