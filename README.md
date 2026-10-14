# ESP32-CAN-Dashboard
An embedded systems project that uses ESP32 microcontrollers and CAN bus communication to simulate, transmit, receive, and display vehicle data in real time.

The project combines C++ firmware, CAN communication, MATLAB/Simulink modeling, and custom PCB design to demonstrate hardware/software integration for automotive electronics.

# Project Overview
The system uses two ESP32 microcontrollers connected through SN65HVD230 CAN transceivers.

* Transmitter (Simulated Vehicle): Generates vehicle data, including engine RPM, speed, and coolant temperature, and transmits it over CAN.

* Receiver (Dashboard): Receives and decodes CAN messages and displays the vehicle data on a 128×64 OLED screen.

A custom PCB was designed in KiCad to integrate the dashboard ESP32, CAN interface, OLED connections, power regulation, and external CAN connections.

# Hardware Components
* 2 ESP32-WROOM-32 development boards (bench testing)

* SN65HVD230 CAN transceiver modules

* SSD1306 128×64 I²C OLED display

* MP1584EN adjustable buck converter module (for PCB assembly)

* Custom designed PCB

* 120 Ω CAN termination resistor and jumper

* Screw terminals, headers, and supporting passive components


# Tech/Tools Used:

Category                Technologies


* Programming           C/C++, Arduino IDE


* Microcontrollers      ESP32


* Communication         CAN Bus, ESP32 TWAI


* PCB Design            KiCad


* Simulation           MATLAB/Simulink


* Interfaces           I²C, OLED


* Debugging            Serial Monitor, Multimeter


