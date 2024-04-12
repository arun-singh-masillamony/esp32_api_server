#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

const char* ssid = "Ashwini PG 0G 2.4G";
const char* password = "lucky00g";
IPAddress static_ip(192, 168, 0, 140); // Static IP address
IPAddress gateway(192, 168, 0, 1);      // Gateway IP address
IPAddress subnet(255, 255, 255, 0);     // Subnet mask

AsyncWebServer server(80);

int readWaterLevel() {
  // Replace this with your actual code to read the water level
  return 75; // Example placeholder value for demonstration
}

void setup() {
  Serial.begin(115200);
  Serial.println("Begining to connect to WiFi..");

  // Connect to Wi-Fi with static IP configuration
  WiFi.config(static_ip, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  
  Serial.println("Connected to the WiFi network");
  Serial.println("IP address: " + WiFi.localIP().toString());
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hello, this is ESP32 REST API!");
  });
  
  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", "Hello from ESP32!");
  });

  server.on("/water_level", HTTP_GET, [](AsyncWebServerRequest *request) {
    int waterLevel = readWaterLevel(); // Read the water level
    StaticJsonDocument<200> doc;
    doc["water_level"] = waterLevel;
    String jsonStr;
    serializeJson(doc, jsonStr);
    request->send(200, "application/json", jsonStr);
  });
  
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
  });
  
  server.begin();
}

void loop() {
  // Nothing to do here as all the functionality is in setup()
}
