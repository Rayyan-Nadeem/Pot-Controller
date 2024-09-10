#include <Arduino.h>

// put function declarations here:
// Define the LED pin
int ledPin = 13;

void setup() {
  // Initialize the digital pin as an output
  Serial.begin(9600);
  
  }

void loop() {
  // // Turn the LED on (HIGH is the voltage level)
  // digitalWrite(ledPin, HIGH);
  // // Wait for 1 second
  // delay(1000);
  // // Turn the LED off by making the voltage LOW
  // digitalWrite(ledPin, LOW);
  // // Wait for 1 second
  // delay(1000);

  int Moisture = analogRead(A0);
  Serial.print("level: ");
  Serial.println(Moisture);
  delay(200);

}
