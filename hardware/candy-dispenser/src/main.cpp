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
#define SERVO_PIN D3

/*************************/
/******* ENDPOINTS *******/
/*************************/

/**
 * @brief Handle the dispense request
 *
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
  serverAngle(45);

  // Wait for the specified number of seconds
  int delayTime = duration * 1000;
  delay(delayTime);

  // Move the servo back to 0 degrees
  serverAngle(0);

  server.send(200, "text/plain", "Dispense complete");
}

/**
 * @brief Handle the set angle request
 *
 * @param angle
 *
 * This function is called when the user makes a request to the /set_angle endpoint.
 *
 * The request should contain a "angle" parameter, which specifies the angle to move the servo to.
 *
 */
void handleSetAngle()
{
  String angleStr = server.arg("angle");
  if (angleStr == "")
  {
    server.send(400, "text/plain", "Missing angle parameter");
    return;
  }

  int angle = angleStr.toInt();

  // Check if the duration is valid
  if (angle <= 0)
  {
    server.send(400, "text/plain", "Invalid angle");
    return;
  }
  if (angle < 0 || angle > 180)
  {
    server.send(400, "text/plain", "Angle must be between 0 and 180");
    return;
  }

  Serial.print("Moving servo to ");
  Serial.print(angle);
  Serial.println(" degrees");

  serverAngle(angle);
  server.send(200, "text/plain", "Servo moved");
}

/**
 * @brief Handle the LED on request
 *
 * This function is called when the user makes a request to the /led_on endpoint.
 *
 * The function will respond with a 200 OK response, and the text "LED on".
 *
 */
void handleLedOn()
{
  ledOn();
  server.send(200, "text/plain", "LED on");
}

/**
 * @brief Handle the LED off request
 *
 * This function is called when the user makes a request to the /led_off endpoint.
 *
 * The function will respond with a 200 OK response, and the text "LED off".
 *
 */
void handleLedOff()
{
  ledOff();
  server.send(200, "text/plain", "LED off");
}

/**
 * @brief Handle the blink request
 *
 * This function is called when the user makes a request to the /blink endpoint.
 *
 * The function will respond with a 200 OK response, and the text "Blink complete".
 *
 */
void handleLedBlink()
{
  for (int i = 0; i < 10; i++)
  {
    ledOn();
    delay(100);
    ledOff();
    delay(100);
  }

  server.send(200, "text/plain", "Blink complete");
}

/*************************/
/******* HARDWARE ********/
/*************************/

/**
 * @brief Handle the server angle request
 *
 * @param angle
 */
void serverAngle(int angle)
{
  candyServo.write(angle);
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

/*************************/
/******* MAIN LOOP *******/
/*************************/

void setup()
{
  // Set up Serial Monitor
  Serial.begin(115200);

  // Setup Servo
  candyServo.attach(SERVO_PIN);
  candyServo.write(0);

  // Setup LED
  pinMode(LED_PIN, OUTPUT);
  ledOff();
  
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
  server.on("/", []()
            { server.send(200, "text/plain", "Hello from the ESP8266!"); });
  server.on("/heartbeat", []()
            { server.send(200, "text/plain", "OK"); });
  server.on("/dispense", handleDispense);
  server.on("/led_blink", handleLedBlink);
  server.on("/led_on", handleLedOn);
  server.on("/led_off", handleLedOff);
  server.on("/set_angle", handleSetAngle);

  server.begin();
  Serial.println("Web server started");
}

void loop()
{
  server.handleClient();
}
