#include <Arduino.h>

constexpr uint8_t LED_PIN = 9;
constexpr uint8_t BUTTON_PIN = 2;

bool ledState = false;

int lastReading = HIGH;
int buttonState = HIGH;

unsigned long lastDebounceTime = 0;
constexpr unsigned long DEBOUNCE_MS = 50;

void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  digitalWrite(LED_PIN, LOW);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_MS) {

    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        ledState = !ledState;

        digitalWrite(LED_PIN, ledState ? HIGH : LOW);

        Serial.println(ledState ? "LED ON" : "LED OFF");
      }
    }
  }

  lastReading = reading;
}

