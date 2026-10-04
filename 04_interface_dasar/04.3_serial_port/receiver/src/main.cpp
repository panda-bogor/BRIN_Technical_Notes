
#include <Arduino.h>
#include <SoftwareSerial.h>

// =====================================
// Pin Declaration
// =====================================

constexpr uint8_t SOFT_RX_PIN = 10;
constexpr uint8_t SOFT_TX_PIN = 11;

// SoftwareSerial(RX, TX)
SoftwareSerial boardLink(SOFT_RX_PIN, SOFT_TX_PIN);

// =====================================
// Receive Buffer
// =====================================

char receiveBuffer[24];
uint8_t receiveIndex = 0;

// =====================================
// Print Received Data
// =====================================

void printReceivedLine() {
  receiveBuffer[receiveIndex] = '\0';

  Serial.print("Counter diterima: ");
  Serial.println(receiveBuffer);

  receiveIndex = 0;
}

// =====================================
// Setup
// =====================================

void setup() {
  Serial.begin(9600);
  boardLink.begin(9600);

  Serial.println("Receiver siap");
}

// =====================================
// Main Loop
// =====================================

void loop() {

  while (boardLink.available() > 0) {

    const char incoming =
        static_cast<char>(boardLink.read());

    // End of message
    if (incoming == '\n') {
      printReceivedLine();
    }

    // Ignore carriage return
    else if (incoming != '\r') {

      if (receiveIndex < sizeof(receiveBuffer) - 1) {
        receiveBuffer[receiveIndex++] = incoming;
      }

      else {
        receiveIndex = 0;
        Serial.println("Buffer overflow, data dibuang");
      }
    }
  }
}
