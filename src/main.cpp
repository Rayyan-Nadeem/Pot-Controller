#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"  // Include Wi-Fi and MQTT configuration from your config.h file

WiFiClient espClient;
PubSubClient client(espClient);

int ledPin = D4;  // LED pin on NodeMCU

// Function prototypes
void mqttCallback(char* topic, byte* payload, unsigned int length);
void blinkLED(int times);
void reconnectWiFi();
void reconnectMQTT();

void setup() {
  Serial.begin(baudRate);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);  // LED off initially

  reconnectWiFi();  // Connect to Wi-Fi
  reconnectMQTT();  // Connect to the MQTT broker
}

void loop() {


  if (!client.connected()) {
    reconnectMQTT();  // Reconnect to MQTT if disconnected
  }
  client.loop();  // Ensure MQTT messages are processed
}

// Function to reconnect to Wi-Fi
void reconnectWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// Function to reconnect to MQTT broker
void reconnectMQTT() {
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    
    // Attempt to connect to the MQTT broker
    if (client.connect("NodeMCUClient")) {
      Serial.println("Connected to MQTT");
      client.subscribe("nodeMCU/blink");
    } else {
      Serial.print("NodeMCU IP Address: ");
      Serial.println(WiFi.localIP());
      Serial.print("Failed to connect to MQTT, rc=");
      Serial.print(client.state());  // Print connection state for better debugging
      Serial.println(". Trying again in 5 seconds...");
      delay(5000);  // Wait before retrying
    }
  }
}


// Callback function to handle incoming MQTT messages
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  Serial.println(message);

  // Check if the message is "blink" and blink the LED
  if (String(topic) == "nodeMCU/blink" && message == "blink") {
    blinkLED(3);
  }
}

// Function to blink the LED
void blinkLED(int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPin, HIGH);  // Turn LED on
    delay(500);                  // Wait 500ms
    digitalWrite(ledPin, LOW);   // Turn LED off
    delay(500);                  // Wait 500ms
  }
}
