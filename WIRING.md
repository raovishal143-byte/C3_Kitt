# Wiring — ESP32-C3 Super Mini KITT LEDs

## GPIO assignment

| Function | Board label | GPIO |
|---|---:|---:|
| Left headlight | 0 | GPIO0 |
| Right headlight | 1 | GPIO1 |
| Scanner LED 1 (leftmost) | 3 | GPIO3 |
| Scanner LED 2 | 4 | GPIO4 |
| Scanner LED 3 | 5 | GPIO5 |
| Scanner LED 4 (rightmost) | 10 | GPIO10 |

## Connect each LED

For every ordinary 2-pin LED:
1. GPIO -> 330 Ω resistor -> LED anode (long leg, +)
2. LED cathode (short leg, flat edge, -) -> GND

Repeat with a separate resistor for all six LEDs. Do not share one resistor between LEDs.

## Important
- Use the GPIO label shown in the table, not the physical pin count.
- GPIO2, GPIO8 and GPIO9 are avoided because they are ESP32-C3 boot-strapping pins.
- GPIO20 and GPIO21 are left free for serial/UART.
- GPIO4 and GPIO5 have alternate JTAG/ADC functions but can be used as digital outputs in this project.
- Keep LED current modest; do not connect high-current lamps directly to GPIO.
- Disconnect USB power before changing wiring.
- Board clones can differ. Check the silkscreen and board revision before connecting LEDs.
