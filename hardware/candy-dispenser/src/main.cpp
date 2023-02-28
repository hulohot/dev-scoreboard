#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Servo.h>

#include "secrets.h"

// Replace with your network credentials
const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

// Define web server on port 80
ESP8266WebServer server(80);

// Create a servo object
Servo candyServo;

// Define GPIO pins
#define LED_PIN 4

/**
 * @brief Handle the dispense request
 * @arg duration: The duration to dispense for
 *
 * This function is called when the user makes a request to the /dispense endpoint.
 *
 * The request should contain a "duration" parameter, which specifies how long the
 * servo should be activated for.
 *
 * For example, a request to /dispense?duration=5 will activate the servo for 5 seconds.
 *
 * The function will respond with a 200 OK response, and the text "Dispense complete".
 *
 * If the request does not contain a "duration" parameter, the function will respond
 * with a 400 Bad Request response, and the text "Missing duration parameter".
 *
 */
void handleDispense()
{
  // Get the value of the "duration" request parameter
  String durationStr = server.arg("duration");

  // If the "duration" parameter is missing, return a 400 Bad Request response
  if (durationStr == "")
  {
    server.send(400, "text/plain", "Missing duration parameter");
    return;
  }

  int duration = durationStr.toInt();

  // Check if the duration is valid
  if (duration <= 0)
  {
    server.send(400, "text/plain", "Invalid duration");
    return;
  }
  if (duration < 1 || duration > 10)
  {
    server.send(400, "text/plain", "Duration must be between 1 and 10 seconds");
    return;
  }

  Serial.print("Dispensing for ");
  Serial.print(duration);
  Serial.println(" seconds");

  // Move the servo to 45 degrees
  candyServo.write(45);

  // Wait for the specified number of seconds
  delay(duration * 1000);

  // Move the servo back to 0 degrees
  candyServo.write(0);

  server.send(200, "text/plain", "Dispense complete");
}

/**
 * @brief Turn the LED on
 * 
 */
void ledOn()
{
  digitalWrite(D4, HIGH);
}

/**
 * @brief Turn the LED off
 * 
 */
void ledOff()
{
  digitalWrite(D4, LOW);
}

void handleBlink()
{
  for (int i = 0; i < 10; i++)
  {
    ledOn();
    delay(100);
    ledOff();
    delay(100);
  }
}

void setup()
{
  Serial.begin(115200);
  candyServo.attach(D3);
  candyServo.write(0);
  delay(1000);

  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print the local IP address of the ESP8266 board
  Serial.print("Connected to Wi-Fi. Local IP address: ");
  Serial.println(WiFi.localIP());

  // Set up the web server
  server.on("/dispense", handleDispense);
  server.on("/blink", handleBlink);
  server.begin();
  Serial.println("Web server started");
}

void loop()
{
  server.handleClient();
}
