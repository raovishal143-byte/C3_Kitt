/*
  C3_Kitt — ESP32-C3 Super Mini
  Five-LED scanner with a two-LED fading tail.

  LED order, left to right:
    LED 1 -> GPIO2
    LED 2 -> GPIO0
    LED 3 -> GPIO6
    LED 4 -> GPIO10
    LED 5 -> GPIO21

  Wiring per LED:
    GPIO -> series resistor -> LED anode (+)
    LED cathode (-) -> GND

  Brightness:
    Moving/main LED       = 100%
    Immediately trailing =  50%
    All other LEDs        =   0%

  Movement:
    Left to right, then right to left.
    200 ms per position.
*/

#include <Arduino.h>

constexpr uint8_t LED_PINS[] = {2, 0, 6, 10, 21};
constexpr int8_t LED_COUNT = sizeof(LED_PINS) / sizeof(LED_PINS[0]);

constexpr uint8_t MAIN_BRIGHTNESS = 255;  // 100% (8-bit PWM)
constexpr uint8_t TAIL_BRIGHTNESS = 128;  // approx. 50%
constexpr uint32_t STEP_TIME_MS = 200;

int8_t position = 0;
int8_t direction = 1;
uint32_t lastStep = 0;

void showScanner(int8_t mainPosition, int8_t travelDirection) {
  // Turn all LEDs off before applying the two brightness levels.
  for (uint8_t i = 0; i < LED_COUNT; ++i) {
    analogWrite(LED_PINS[i], 0);
  }

  // Main moving LED.
  analogWrite(LED_PINS[mainPosition], MAIN_BRIGHTNESS);

  // The LED immediately behind the moving head.
  const int8_t tailPosition = mainPosition - travelDirection;
  if (tailPosition >= 0 && tailPosition < LED_COUNT) {
    analogWrite(LED_PINS[tailPosition], TAIL_BRIGHTNESS);
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
