
#include <Arduino.h>

// =====================================
// Pin Declaration
// =====================================

const int POT_PIN = A0;

// =====================================
// Setup
// =====================================

void setup() {
  Serial.begin(9600);
}

// =====================================
// Main Loop
// =====================================

void loop() {

  // Read analog input (10-bit: 0-1023)
  int adcValue = analogRead(POT_PIN);

  // Display ADC value
  Serial.print("ADC: ");
  Serial.println(adcValue);

  // Sampling interval: 500 ms
  delay(500);
}
