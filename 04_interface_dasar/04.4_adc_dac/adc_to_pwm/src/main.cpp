
#include <Arduino.h>

// =====================================
// Pin Declaration
// =====================================

const int POT_PIN = A0;
const int PWM_PIN = 9;

// =====================================
// Setup
// =====================================

void setup() {
  Serial.begin(9600);

  pinMode(PWM_PIN, OUTPUT);
}

// =====================================
// Main Loop
// =====================================

void loop() {

  // Read ADC (10-bit: 0-1023)
  int adcValue = analogRead(POT_PIN);

  // Convert ADC 10-bit to PWM 8-bit
  int pwmValue = map(adcValue, 0, 1023, 0, 255);

  // Generate PWM signal on D9
  analogWrite(PWM_PIN, pwmValue);

  // Display ADC and PWM values
  Serial.print("ADC = ");
  Serial.print(adcValue);

  Serial.print(" | PWM = ");
  Serial.println(pwmValue);

  delay(1000);
}
