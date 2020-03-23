# ArduinoVentilator

Designed for a Heltec ESP32 (https://www.amazon.fr/Affichage-Conseil-d%C3%A9veloppement-Arduino-Nodemcu/dp/B078MCR8FY).
Based on the https://opensourceventilator.ie/ project.

## Hardware interfaces

Inputs : works with 3 potentiometers and 2 press buttons.

- Potentiometer #1 for duration between breathes
- Potentiometer #2 for breath duration
- Potentiometer #3 for breathe intensity
- Button #1 for working mode
- Button #2 for release mode


Outputs : one motor and the OLED screen of the ESP32
An input pin is used to get current motor position.

## Software interfaces

Use the ESP32 power to transmit data through wifi and MQTT protocol.