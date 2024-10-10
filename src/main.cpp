#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "config.h"  // Include the config file

int ledPin = 13; // Define the LED pin

unsigned long previousMillis = 0; // Store the last time the GET request was made
const long interval = 10000; // Interval for sending the GET request (10 seconds)

WiFiClient client; // Create a WiFiClient object

void setup() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Turn the LED off initially

  Serial.begin(9600);
  Serial.println();
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  // Wait until the NodeMCU is connected to the Wi-Fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  digitalWrite(ledPin, HIGH); // Turn the LED on when connected
  Serial.println();
  Serial.println("WiFi Connected Successfully!");
  Serial.print("NodeMCU IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if 10 seconds have passed
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Update the last time we sent the GET request

    // Check if Wi-Fi is still connected
    if (WiFi.status() == WL_CONNECTED) {
      HTTPClient http;  // Create an HTTPClient object

      // Specify the URL for the HTTP GET request, using WiFiClient object
      http.begin(client, serverUrl);

      // Send the HTTP GET request
      int httpCode = http.GET();

      // Check for a successful response
      if (httpCode > 0) {
        // HTTP response code is successful
        String payload = http.getString(); // Get the response payload
        Serial.println("Response from server:");
        Serial.println(payload); // Print the response to the Serial Monitor
      } else {
        Serial.println("Error on HTTP request"); // In case of an error
      }

      http.end(); // Close the connection
    } else {
      Serial.println("WiFi not connected");
    }
  }
}
