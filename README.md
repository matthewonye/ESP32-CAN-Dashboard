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

* SSD1306 128×64 OLED display

* MP1584EN adjustable buck converter module (for PCB assembly)

* Custom designed PCB

* 120 Ω CAN termination resistor and jumper

* Screw terminals, headers, and supporting passive components


# Tech/Tools Used:


* Programming      |     C/C++, Arduino IDE


* Microcontrollers   |   ESP32


* Communication     |    CAN Bus, ESP32 TWAI


* PCB Design      |      KiCad


* Simulation      |     MATLAB/Simulink


* Interfaces     |       OLED


* Debugging       |     Serial Monitor, Multimeter


# System Architecture

Simulated Vehicle ESP32 → SN65HVD230 → CAN Bus → SN65HVD230 → Dashboard ESP32 → OLED Display

The transmitter generates simulated vehicle signals and packages them into CAN messages. The receiver reconstructs the transmitted values and updates the OLED display.

# CAN Communication

The system uses the ESP32's built-in TWAI controller with external SN65HVD230 transceivers.


CAN Configuration

* Bit rate: 500 kbps
* CAN message ID: 0x100
* Payload length: 5 bytes


Byte/Data

* 0 | RPM High

* 1 | RPM Low

* 2 | Vehicle Speed

* 3 | Coolant Temp

* 4 | Reserved

where RPM is encoded as a 16-bit value and reconstructed by the receiver using bitwise operations.

# [MATLAB/Simulink](https://github.com/matthewonye/ESP32-CAN-Dashboard/tree/main/Simulink)

Developed a Simulink model to simulate vehicle signals and demonstrate CAN payload encoding and decoding.

The model includes:

* Simulated RPM, speed, and coolant temperature signals
* Signal saturation and data-type conversion
* High-byte/low-byte encoding
* Byte-level payload construction
* Decoding and reconstruction of transmitted values


The Simulink model validates the data processing logic; physical CAN communication is handled by the ESP32 hardware and firmware.

# [Custom PCB Design](https://github.com/matthewonye/ESP32-CAN-Dashboard/tree/main/PCB/KiCAD/CAN_Dashboard_PCB)

Designed a multi layer PCB in KiCad to integrate the dashboard hardware into a single assembly.

PCB features:
* ESP32 DevKit footprint

* SN65HVD230 module interface

* OLED connector

* External CANH/CANL/GND connector

* Buck-converter power section

* Switchable 120 Ω CAN termination

* Power indicator LED

* Signal and power test points

* Ground copper plane

* ESP32 antenna copper keepout

# Testing and Validation
* Established CAN communication between two ESP32 development boards

* Verified message transmission and reception

* Decoded vehicle data and displayed it on the OLED

* Validated signal encoding and decoding in MATLAB/Simulink

* Completed KiCad electrical and PCB design-rule checks


# Future Additions 
* Integrate an Assembly routine for low-level data processing

* Add vehicle-data logging capabilities

* Expand dashboard visualization

* Evaluate a protected, listen-only interface for real vehicle CAN networks

# Author
Matthew Onye

Computer Engineering | University of Michigan–Dearborn

[LinkedIn](https://www.linkedin.com/in/matthew-onye-9a4964316/?isSelfProfile=true)

