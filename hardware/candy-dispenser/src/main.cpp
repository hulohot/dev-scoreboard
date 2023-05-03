#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <Servo.h>

#define SERVO_PIN D0

// Replace with your network credentials
const char* ssid = "BrickHouse";
const char* password = "Olivia1Ethan2Jacob3";

// Set the IP address of the server you want to connect to
const char* serverIP = "192.168.1.100";
const int serverPort = 80;

ESP8266WebServer server(80);
Servo myservo;

void handleDispense() {
  // Get the value of the "duration" request parameter
  String durationStr = server.arg("duration");
  int duration = durationStr.toInt();
  
  Serial.print("Dispensing for ");
  Serial.print(duration);
  Serial.println(" seconds");


  // Move the servo to 180 degrees
  myservo.write(90);
  digitalWrite(LED_BUILTIN, HIGH);

  // Wait for the specified number of seconds
  delay(duration * 500);

  // Move the servo back to 0 degrees
  myservo.write(0);
  digitalWrite(LED_BUILTIN, LOW);

  // Stop the servo from moving
  myservo.detach();

  server.send(200, "text/plain", "Dispense complete");
}

void setup() {
  Serial.begin(115200);
  myservo.attach(D0);
  myservo.write(0);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

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
