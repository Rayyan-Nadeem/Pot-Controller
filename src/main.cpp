#include <Arduino.h>

// Define the LED pin (D4 on NodeMCU corresponds to GPIO 2)
int ledPin = D4;

void setup() {
  // Initialize serial communication at 9600 baud
  Serial.begin(9600);

  // Set the LED pin as output
  pinMode(ledPin, OUTPUT);

  // Initially turn off the LED
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Turn the LED on (active LOW)
  digitalWrite(ledPin, LOW); 
  // Print "Hello" to the serial monitor
  Serial.println("Hello");
  // Wait for a second
  delay(1000);

  // Turn the LED off
  digitalWrite(ledPin, HIGH);
  // Print "Hello" again
  Serial.println("Hello");
  // Wait for a second
  delay(1000);
}
