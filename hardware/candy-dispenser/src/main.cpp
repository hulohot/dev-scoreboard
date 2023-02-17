#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#include "secrets.h"

// Replace with your network credentials
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

ESP8266WebServer server(80);
Servo myservo;

void handleDispense() {
  // Get the value of the "duration" request parameter
  String durationStr = server.arg("duration");
  int duration = durationStr.toInt();
  
  Serial.print("Dispensing for ");
  Serial.print(duration);
  Serial.println(" seconds");

  // Move the servo to 45 degrees
  myservo.write(45);

  // Wait for the specified number of seconds
  delay(duration * 1000);

  // Move the servo back to 0 degrees
  myservo.write(0);

  server.send(200, "text/plain", "Dispense complete");
}

void setup() {
  Serial.begin(115200);
  myservo.attach(D3);
  myservo.write(0);
  delay(1000);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  // Print the local IP address of the ESP8266 board
  Serial.print("Connected to Wi-Fi. Local IP address: ");
  Serial.println(WiFi.localIP());

  // Set up the web server
  server.on("/dispense", handleDispense);
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
}
