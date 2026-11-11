# C3 KITT — ESP32-C3 Super Mini

Standalone five-LED KITT / Knight Rider-style scanner for the ESP32-C3 Super Mini.

## Current hardware configuration

Five LEDs, connected left to right:

1. GPIO2
2. GPIO0
3. GPIO6
4. GPIO10
5. GPIO21

Each LED is connected as GPIO -> series resistor -> LED anode (+), with the LED cathode (-) connected to GND. Each LED has its own resistor.

## Behaviour

- One red LED lights at a time.
- The illuminated LED sweeps from left to right.
- The scanner reverses and sweeps right to left continuously.
- Default step time is 90 ms.
- Change `SCAN_STEP_MS` in `firmware/C3_Kitt/C3_Kitt.ino` to adjust speed.

## Build

This is an Arduino-framework PlatformIO project. Run:

```sh
pio run
```

The GitHub Actions workflow builds the firmware and uploads `firmware.bin` as the `C3_Kitt-firmware` artifact.

## Pin note

GPIO2 is an ESP32-C3 strapping pin; ensure its LED circuit does not interfere with reset-time boot strapping. GPIO21 is commonly UART0 TX and is used here as a scanner output.
