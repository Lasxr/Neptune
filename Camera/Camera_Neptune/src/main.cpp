#include "esp_camera.h"
#include <WiFi.h>

// --- WiFi config ---
const char* ssid = "Atsc-2.4G";
const char* password = "1245@atsc";

// --- Camera pins for AI Thinker ESP32-CAM ---
#define PWDN_GPIO_NUM    -1
#define RESET_GPIO_NUM   -1
#define XCLK_GPIO_NUM     0
#define SIOD_GPIO_NUM    26
#define SIOC_GPIO_NUM    27

#define Y9_GPIO_NUM      35
#define Y8_GPIO_NUM      34
#define Y7_GPIO_NUM      39
#define Y6_GPIO_NUM      36
#define Y5_GPIO_NUM      21
#define Y4_GPIO_NUM      19
#define Y3_GPIO_NUM      18
#define Y2_GPIO_NUM       5
#define VSYNC_GPIO_NUM   25
#define HREF_GPIO_NUM    23
#define PCLK_GPIO_NUM    22

WiFiServer server(80);
int flashLedPin = 4; // ใช้ขา GPIO4 เป็นไฟ LED แฟลช (ถ้ามี)

// ฟังก์ชันตั้งค่า LED แฟลช
void setupLedFlash(int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW); // ปิดแฟลชก่อน
}

// ฟังก์ชันเริ่มต้นเว็บเซิร์ฟเวอร์กล้อง
void startCameraServer() {
  server.begin();
  Serial.println("Camera server started");
}

// ส่งภาพ JPEG เป็น HTTP response
void handleClient() {
  Serial.println("Start");
  WiFiClient client = server.available();
  if (!client) return;

  Serial.println("Client connected");
  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n\r\n";
  client.print(response);

  while (client.connected()) {
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      break;
    }

    client.printf("--frame\r\n");
    client.printf("Content-Type: image/jpeg\r\n");
    client.printf("Content-Length: %u\r\n\r\n", fb->len);
    client.write(fb->buf, fb->len);
    client.printf("\r\n");
    esp_camera_fb_return(fb);

    if (!client.connected()) break;
    delay(100); // ปรับความถี่ส่งภาพ (fps)
  }
  client.stop();
  Serial.println("Client disconnected");
}

void setup() {
  Serial.begin(115200);
  setupLedFlash(flashLedPin);

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer   = LEDC_TIMER_0;
  config.pin_d0       = Y2_GPIO_NUM;
  config.pin_d1       = Y3_GPIO_NUM;
  config.pin_d2       = Y4_GPIO_NUM;
  config.pin_d3       = Y5_GPIO_NUM;
  config.pin_d4       = Y6_GPIO_NUM;
  config.pin_d5       = Y7_GPIO_NUM;
  config.pin_d6       = Y8_GPIO_NUM;
  config.pin_d7       = Y9_GPIO_NUM;
  config.pin_xclk     = XCLK_GPIO_NUM;
  config.pin_pclk     = PCLK_GPIO_NUM;
  config.pin_vsync    = VSYNC_GPIO_NUM;
  config.pin_href     = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;  // ใช้ชื่อใหม่แทน pin_sscb_sda ที่ deprecated
  config.pin_sccb_scl = SIOC_GPIO_NUM;  // ใช้ชื่อใหม่แทน pin_sscb_scl ที่ deprecated
  config.pin_pwdn     = PWDN_GPIO_NUM;
  config.pin_reset    = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_QVGA;  // 320x240
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_QVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  if (esp_camera_init(&config) != ESP_OK) {
    Serial.println("Camera init failed");
    while(true) { delay(1000); }
  }

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("Camera Stream Ready at: http://");
  Serial.println(WiFi.localIP());

  startCameraServer();
}

void loop() {
  handleClient();
}
