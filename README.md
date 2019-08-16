# ThermostatControl
Jigar Hira

Navid Bazmoon

Code to interface the NEST thermostat with ESP32

Utilizes the RMT ESP32 library to send IR signals controlling a portable AC unit.

## IR Transmission
ESP32 has built-in hardware for handling IR Codes.
The RMT library feeds the hardware two signals:

1)	Data signal which represents the 0 and 1 bits
2)	Carrier frequency square wave

The hardware in the ESP32 modulates the data signal using the square wave to produce the IR signal (more information can be found here: https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/rmt.html).

## NEST signals
In order to interface with the NEST smart thermostat, we use a simple circuit to convert 24VAC thermostat signals to lower voltage DC signals.

This allows us to use the GPIO pins on the ESP32 to detect what the NEST has turned on or off.

### NOTE:
This project is still in development


