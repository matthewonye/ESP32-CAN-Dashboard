# ESP32-CAN-Dashboard
An embedded systems project that uses ESP32 microcontrollers and CAN bus communication to simulate, transmit, receive, and display vehicle data in real time.

The project combines C++ firmware, CAN communication, MATLAB/Simulink modeling, and custom PCB design to demonstrate hardware/software integration for automotive electronics.

# Project Overview
The system uses two ESP32 microcontrollers connected through SN65HVD230 CAN transceivers.

* Transmitter (Simulated Vehicle): Generates vehicle data, including engine RPM, speed, and coolant temperature, and transmits it over CAN.

* Receiver (Dashboard): Receives and decodes CAN messages and displays the vehicle data on a 128×64 OLED screen.
