/*
  KITT scan — ESP32-C3 Super Mini
  Five-LED scanner with a two-LED trailing fade.

  Final LED order, left to right:
    LED 1 (Left)   -> GPIO1
    LED 2          -> GPIO10
    LED 3 (Centre) -> GPIO21
    LED 4          -> GPIO0
    LED 5 (Right)  -> GPIO3

  Wiring per LED:
    GPIO -> series resistor -> LED anode (+)
    LED cathode (-) -> GND

  Brightness:
    Moving/main LED          = 100%
    First trailing LED       =  25%
    Second trailing LED      =  15%
    All other LEDs           =   0%

  Movement:
    Left to right, then right to left.
    200 ms per position.

  No buzzer/audio output is included.
*/

#include <Arduino.h>

constexpr uint8_t LED_PINS[] = {1, 10, 21, 0, 3};
constexpr int8_t LED_COUNT = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

constexpr uint8_t MAIN_BRIGHTNESS = 255;  // 100% (8-bit PWM)
constexpr uint8_t FIRST_TAIL_BRIGHTNESS = 64;  // approx. 25%
constexpr uint8_t SECOND_TAIL_BRIGHTNESS = 38; // approx. 15%
constexpr uint32_t STEP_TIME_MS = 200;

int8_t position = 0;
int8_t direction = 1;
uint32_t lastStep = 0;

void showScanner(int8_t mainPosition, int8_t travelDirection) {
  // Turn all LEDs off before applying the three brightness levels.
  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    analogWrite(LED_PINS[i], 0);
  }

  // Main moving LED.
  analogWrite(LED_PINS[mainPosition], MAIN_BRIGHTNESS);

  // First trailing LED, immediately behind the moving head.
  const int8_t firstTailPosition = mainPosition - travelDirection;
  if (firstTailPosition >= 0 && firstTailPosition < LED_COUNT) {
    analogWrite(LED_PINS[firstTailPosition], FIRST_TAIL_BRIGHTNESS);
  }

  // Second trailing LED, one more position behind the first tail.
  const int8_t secondTailPosition = mainPosition - (2 * travelDirection);
  if (secondTailPosition >= 0 && secondTailPosition < LED_COUNT) {
    analogWrite(LED_PINS[secondTailPosition], SECOND_TAIL_BRIGHTNESS);
  }
}

void setup() {
  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    pinMode(LED_PINS[i], OUTPUT);
    analogWrite(LED_PINS[i], 0);
  }

  position = 0;
  direction = 1;
  showScanner(position, direction);
  lastStep = millis();
}

void loop() {
  const uint32_t now = millis();

  if (now - lastStep >= STEP_TIME_MS) {
    lastStep = now;

    int8_t nextPosition = position + direction;

    // Reverse at either end, without skipping an endpoint.
    if (nextPosition < 0 || nextPosition >= LED_COUNT) {
      direction = -direction;
      nextPosition = position + direction;
    }

    position = nextPosition;
    showScanner(position, direction);
  }
}
