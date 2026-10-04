
#include <Arduino.h>
#include <SoftwareSerial.h>

// =====================================
// Pin Declaration
// =====================================

constexpr uint8_t BUTTON_PIN = 2;
constexpr uint8_t LED_PIN = 9;

constexpr uint8_t SOFT_RX_PIN = 10;
constexpr uint8_t SOFT_TX_PIN = 11;

// SoftwareSerial(RX, TX)
SoftwareSerial boardLink(SOFT_RX_PIN, SOFT_TX_PIN);

// =====================================
// Debounce Configuration
// =====================================

constexpr unsigned long DEBOUNCE_MS = 50;

bool ledState = false;

int lastRawState = HIGH;
int stableButtonState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long counter = 0;

// =====================================
// Send Counter
// =====================================

void sendCounter() {
  boardLink.println(counter);

  Serial.print("Kirim Counter: ");
  Serial.print(counter);

  Serial.print(" | LED ");
  Serial.println(ledState ? "NYALA" : "MATI");
}

// =====================================
// Setup
// =====================================

void setup() {
  Serial.begin(9600);
  boardLink.begin(9600);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);

  Serial.println("Sender siap");
}

// =====================================
// Main Loop
// =====================================

void loop() {
  const unsigned long now = millis();
  const int reading = digitalRead(BUTTON_PIN);

  // Reset timer ketika pembacaan berubah
  if (reading != lastRawState) {
    lastDebounceTime = now;
  }

  // Validasi debounce
  if ((now - lastDebounceTime) >= DEBOUNCE_MS &&
      reading != stableButtonState) {

    stableButtonState = reading;

    // Tombol ditekan (active LOW)
    if (stableButtonState == LOW) {

      ledState = !ledState;
      counter++;

      digitalWrite(LED_PIN, ledState ? HIGH : LOW);

      // Send data to Receiver
      sendCounter();
    }
  }

  lastRawState = reading;
}
