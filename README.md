# C3 KITT — ESP32-C3 Super Mini

A standalone LED controller for a KITT / Knight Rider-style front light bar.

## Hardware
- ESP32-C3 Super Mini (16-pin board: 8 pins per side)
- 2 continuously illuminated headlight LEDs
- 4 red scanner LEDs
- One 220–330 Ω series resistor per LED

## Behaviour
- Both headlights turn on continuously after startup.
- Four red scanner LEDs animate left-to-right and back-to-left.
- Scanner speed and brightness behaviour will be configurable in firmware.

## Safety / wiring
Use one current-limiting resistor per ordinary LED. GPIO pins are 3.3 V logic and must not be used to drive high-current lamps directly. Confirm the exact board pin labels before wiring; the GPIO assignment will be documented in the firmware once verified.

## Firmware
Arduino framework project. See `firmware/C3_Kitt/C3_Kitt.ino`.
