# C3_Kitt — Updated LED Wiring

Board: ESP32-C3 Super Mini

## Five-LED scanner GPIO assignment

| LED position (left to right) | Board GPIO |
|---|---:|
| LED 1 | GPIO2 |
| LED 2 | GPIO0 |
| LED 3 | GPIO6 |
| LED 4 | GPIO10 |
| LED 5 | GPIO21 |

## LED connection

Each LED has its own series resistor:

GPIO -> resistor -> LED anode (+)
LED cathode (-) -> GND

The firmware uses active-HIGH outputs:
- HIGH = LED ON
- LOW = LED OFF

## Important board note

GPIO2 is an ESP32-C3 strapping pin. The board may fail to enter its normal boot mode if external circuitry pulls this pin to an unsuitable level during reset. The LED/resistor connection must not hold GPIO2 low or otherwise interfere with boot. If the board ever fails to boot after wiring, disconnect USB power before checking the GPIO2 LED circuit.

GPIO21 is also commonly used as UART0 TX on ESP32-C3 boards. The scanner firmware uses it as a digital output, so serial output on that pin may not be available while the LED is connected.

Use one resistor per LED. Disconnect USB power before changing wiring.
