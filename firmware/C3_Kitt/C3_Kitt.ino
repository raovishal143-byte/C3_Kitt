/*
  C3_Kitt — ESP32-C3 Super Mini
  2 always-on headlights + 4-LED red KITT scanner.

  Wiring (each LED gets its OWN 330 ohm series resistor):
    Headlight L -> GPIO0
    Headlight R -> GPIO1
    Scanner 1   -> GPIO3
    Scanner 2   -> GPIO4
    Scanner 3   -> GPIO5
    Scanner 4   -> GPIO10
  LED anode (+) -> resistor -> GPIO; LED cathode (-) -> GND.
  Outputs are active HIGH.

  This pin plan avoids GPIO2/8/9 boot-strapping pins and GPIO20/21
  UART pins. Verify the silkscreen and exact board variant before wiring.
*/

#include <Arduino.h>

constexpr uint8_t HEADLIGHT_LEFT  = 0;
constexpr uint8_t HEADLIGHT_RIGHT = 1;
constexpr uint8_t SCAN_PINS[] = {3, 4, 5, 10};
constexpr uint8_t SCAN_COUNT = sizeof(SCAN_PINS) / sizeof(SCAN_PINS[0]);

constexpr uint32_t SCAN_STEP_MS = 110; // Adjust for faster/slower sweep

int8_t scanPosition = 0;
int8_t scanDirection = 1;
uint32_t lastScanStep = 0;

void showScannerPosition(int8_t position) {
  for (uint8_t i = 0; i < SCAN_COUNT; ++i) {
    digitalWrite(SCAN_PINS[i], (i == position) ? HIGH : LOW);
  }
}

void setup() {
  pinMode(HEADLIGHT_LEFT, OUTPUT);
  pinMode(HEADLIGHT_RIGHT, OUTPUT);

  digitalWrite(HEADLIGHT_LEFT, HIGH);
  digitalWrite(HEADLIGHT_RIGHT, HIGH);

  for (uint8_t i = 0; i < SCAN_COUNT; ++i) {
    pinMode(SCAN_PINS[i], OUTPUT);
    digitalWrite(SCAN_PINS[i], LOW);
  }

  scanPosition = 0;
  scanDirection = 1;
  showScannerPosition(scanPosition);
  lastScanStep = millis();
}

void loop() {
  const uint32_t now = millis();
  if (now - lastScanStep >= SCAN_STEP_MS) {
    lastScanStep = now;
    scanPosition += scanDirection;

    if (scanPosition >= static_cast<int8_t>(SCAN_COUNT - 1)) {
      scanPosition = SCAN_COUNT - 1;
      scanDirection = -1;
    } else if (scanPosition <= 0) {
      scanPosition = 0;
      scanDirection = 1;
    }

    showScannerPosition(scanPosition);
  }
}
