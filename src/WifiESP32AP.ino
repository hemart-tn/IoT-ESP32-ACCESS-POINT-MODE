#include <Arduino.h>
#include <WiFi.h>
#include "LittleFS.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// ================= PIN =================
#define trigPin 5
#define echoPin 18

#define RED_PIN   19
#define GREEN_PIN 21
#define BLUE_PIN  22

// ================= WIFI =================
#define AP_SSID "ESP32-ROBOT"
#define AP_PASS "123456789"

// ================= SERVER =================
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

unsigned long previousMillis = 0;
const long interval = 100;

// ================= LITTLEFS =================
void initLittleFS() {
  if(!LittleFS.begin()){
    Serial.println("LittleFS Error");
    return;
  }

  File file = LittleFS.open("/index.html", "r");
  if (!file) {
    Serial.println("index.html tidak ditemukan");
  } else {
    Serial.println("index.html OK");
    file.close();
  }
}

// ================= RGB =================
void setRGB(int r, int g, int b){
  ledcWrite(RED_PIN, r);
  ledcWrite(GREEN_PIN, g);
  ledcWrite(BLUE_PIN, b);
}

// ================= WEBSOCKET =================
void notifyClients(String msg) {
  ws.textAll(msg);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {

  AwsFrameInfo *info = (AwsFrameInfo*)arg;

  if (info->final && info->index == 0 && info->len == len) {

    data[len] = 0;
    String msg = String((char*)data);

    Serial.print("WS Received: ");
    Serial.println(msg);

    int r=0,g=0,b=0;

    if (msg.startsWith("RGB:")) {

      msg.remove(0,4);

      int c1 = msg.indexOf(',');
      int c2 = msg.indexOf(',', c1+1);

      if (c1 > 0 && c2 > c1) {
        r = msg.substring(0,c1).toInt();
        g = msg.substring(c1+1,c2).toInt();
        b = msg.substring(c2+1).toInt();

        setRGB(r,g,b);
      }
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client,
             AwsEventType type, void *arg, uint8_t *data, size_t len) {

  if(type == WS_EVT_CONNECT){
    Serial.println("Client connected");
  }
  else if(type == WS_EVT_DISCONNECT){
    Serial.println("Client disconnected");
  }
  else if(type == WS_EVT_DATA){
    handleWebSocketMessage(arg,data,len);
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

// ================= ULTRASONIC =================
int Read_Distance(){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;
}

// ================= SETUP =================
void setup() {

  Serial.begin(115200);
  delay(3000); // 🔥 penting supaya Serial stabil

  Serial.println("STARTING...");

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // PWM (ESP32 core 3.x)
  ledcAttach(RED_PIN, 5000, 8);
  ledcAttach(GREEN_PIN, 5000, 8);
  ledcAttach(BLUE_PIN, 5000, 8);

  initLittleFS();

  // ===== WIFI =====
  WiFi.softAP(AP_SSID, AP_PASS);

  delay(500);

  Serial.println("WiFi AP STARTED");
  Serial.print("SSID: ");
  Serial.println(AP_SSID);

  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  initWebSocket();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(LittleFS, "/index.html", "text/html");
  });

  server.serveStatic("/", LittleFS, "/");
  server.begin();

  Serial.println("SERVER READY");
}

void loop() {

  static unsigned long lastPrint = 0;

  // Print IP tiap 5 detik
  if (millis() - lastPrint > 5000) {
    lastPrint = millis();
    Serial.print("IP: ");
    Serial.println(WiFi.softAPIP());
  }

  // Kirim jarak tiap interval
  if (millis() - previousMillis >= interval) {
    previousMillis = millis();  // 🔥 FIX DISINI

    int d = Read_Distance();
    notifyClients(String(d));
  }

  ws.cleanupClients();
}