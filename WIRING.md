# C3_Kitt — Updated LED Wiring

Board: ESP32-C3 Super Mini

## Five-LED scanner GPIO assignment

| LED position (left to right) | Board GPIO |
|---|---:|
| LED 1 — Left | GPIO8 |
| LED 2 | GPIO10 |
| LED 3 — Centre | GPIO21 |
| LED 4 | GPIO0 |
| LED 5 — Right | GPIO2 |

## LED connection

Each LED has its own series resistor:

GPIO -> resistor -> LED anode (+)  
LED cathode (-) -> GND

The firmware uses active-HIGH outputs:
- HIGH = LED ON
- LOW = LED OFF

Connect all LED cathodes to the board's GND. Use one resistor per LED. Disconnect USB power before changing wiring.

## Important ESP32-C3 board notes

GPIO2 and GPIO8 are ESP32-C3 strapping pins. External LED circuits must not force these pins to an unsuitable level during reset, or the board may fail to boot. With the LED/resistor connected from GPIO to GND, verify that the circuit does not prevent the required reset-time strapping level. If the board does not boot after wiring, disconnect USB power and check these two LED circuits first.

GPIO21 is commonly used as UART0 TX on ESP32-C3 boards. This scanner uses GPIO21 as an LED output, so serial output on that pin may not be available while the LED is connected.
