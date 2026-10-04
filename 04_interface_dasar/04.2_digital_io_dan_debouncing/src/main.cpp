
#include <Arduino.h>

// =====================================
// Pin Configuration
// =====================================

constexpr uint8_t LED_PIN = 9;
constexpr uint8_t BUTTON_PIN = 2;

// =====================================
// State Variables
// =====================================

bool ledState = false;

int lastReading = HIGH;
int buttonState = HIGH;

// =====================================
// Debounce Configuration
// =====================================

unsigned long lastDebounceTime = 0;
constexpr unsigned long DEBOUNCE_MS = 50;

// Button Press Counter
unsigned long pressCount = 0;

// =====================================
// Setup
// =====================================

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_PIN, LOW);

  Serial.println("Digital Input Output Experiment");
  Serial.println("Debouncing using millis()");
  Serial.println("-------------------------------");
}

// =====================================
// Main Loop
// =====================================

void loop() {

  // Read current button state
  int reading = digitalRead(BUTTON_PIN);

  // Detect changes and reset debounce timer
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  // Check if input has been stable for >50 ms
  if ((millis() - lastDebounceTime) > DEBOUNCE_MS) {

    // Update validated button state
    if (reading != buttonState) {
      buttonState = reading;

      // Valid button press (HIGH to LOW)
      if (buttonState == LOW) {

        // Increment button press counter
        pressCount++;

        // Toggle LED state
        ledState = !ledState;

        digitalWrite(LED_PIN, ledState ? HIGH : LOW);

        // Display results on Serial Monitor
        Serial.print("Button Press Count: ");
        Serial.println(pressCount);

        Serial.print("LED State: ");
        Serial.println(ledState ? "ON" : "OFF");

        Serial.println("-------------------------------");
      }
    }
  }

  // Store previous reading
  lastReading = reading;
}
