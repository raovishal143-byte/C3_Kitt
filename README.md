# C3 KITT — ESP32-C3 Super Mini

Standalone five-LED KITT / Knight Rider-style scanner for the ESP32-C3 Super Mini.

## Current hardware configuration

Five LEDs, connected left to right:

1. LED 1 — Left: GPIO8
2. LED 2: GPIO10
3. LED 3 — Centre: GPIO21
4. LED 4: GPIO0
5. LED 5 — Right: GPIO2

Each LED is connected as GPIO -> series resistor -> LED anode (+), with the LED cathode (-) connected to GND. Each LED has its own resistor.

## Behaviour

- The main red LED sweeps from left to right, then right to left continuously.
- The LED immediately behind the main LED glows at approximately 50% brightness.
- The main LED is at 100% brightness; all other LEDs are off.
- Default step time is 200 ms per position.
- Change `STEP_TIME_MS` in `firmware/C3_Kitt/C3_Kitt.ino` to adjust speed.

## Build

This is an Arduino-framework PlatformIO project. Run:

```sh
pio run
```

The GitHub Actions workflow builds the firmware and uploads `firmware.bin` as the `KITT scan` artifact.

## Pin note

GPIO2 and GPIO8 are ESP32-C3 strapping pins. Ensure the LED circuits do not interfere with reset-time boot strapping. GPIO21 is commonly UART0 TX and is used here as a scanner output.
