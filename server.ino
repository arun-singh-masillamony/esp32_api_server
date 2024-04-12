#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

const char* ssid = "Ashwini PG 0G 2.4G";
const char* password = "lucky00g";
IPAddress static_ip(192, 168, 0, 140); // Static IP address
IPAddress gateway(192, 168, 0, 1);      // Gateway IP address
IPAddress subnet(255, 255, 255, 0);     // Subnet mask

// Input pin
const int trigPin = 14;
// Output pin
const int echoPin = 27;

AsyncWebServer server(80);

float distanceCm;

int readWaterLevel() {
  // Replace this with your actual code to read the water level
  return distanceCm; // Return the distance read from the sensor
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
    float waterLevel = readWaterLevel(); // Read the water level
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
  // Establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long duration;

  // The HC-SR04 sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // The same pin is used to read the signal from the HC-SR04 sensor: a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into distance (cm)
  distanceCm = duration * 0.034 / 2; // Speed of sound is 34 cm/microsecond
  
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  
  delay(100);
}
