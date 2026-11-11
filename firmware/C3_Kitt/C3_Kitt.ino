/*
  C3_Kitt — ESP32-C3 Super Mini
  Updated hardware: FIVE red KITT scanner LEDs only.

  LED GPIO assignment (left to right):
    LED 1 -> GPIO2
    LED 2 -> GPIO0
    LED 3 -> GPIO6
    LED 4 -> GPIO10
    LED 5 -> GPIO21

  Each LED is wired:
    GPIO -> series resistor -> LED anode (+)
    LED cathode (-) -> GND

  Outputs are active HIGH.
  No external libraries required.
*/

#include <Arduino.h>

constexpr uint8_t LED_PINS[] = {2, 0, 6, 10, 21};
constexpr uint8_t LED_COUNT = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

// Adjust this value to change scanner speed.
constexpr uint32_t SCAN_STEP_MS = 90;

int8_t scanPosition = 0;
int8_t scanDirection = 1;
uint32_t lastScanStep = 0;

void showScannerPosition(int8_t position) {
  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    digitalWrite(LED_PINS[i], (i == position) ? HIGH : LOW);
  }
}

void setup() {
  // Configure all five outputs and start with every LED off.
  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
  }

  // Start at the first LED and begin scanning.
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

    // Reverse direction at either end.
    if (scanPosition >= static_cast<int8_t>(LED_COUNT - 1)) {
      scanPosition = LED_COUNT - 1;
      scanDirection = -1;
    } else if (scanPosition <= 0) {
      scanPosition = 0;
      scanDirection = 1;
    }

    showScannerPosition(scanPosition);
  }
}
