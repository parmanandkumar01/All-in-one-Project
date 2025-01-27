# Remote-Control Vehicle Project

A **remote-control vehicle (RCV)** is defined as any mobile device that is controlled externally without restricting its motion. These devices are typically controlled using:
- Radio control devices
- Cables between the control and the vehicle
- Infrared or Bluetooth controllers

An RCV is always controlled by a human and does not take any autonomous actions. It is vital for the vehicle to:
1. Proceed accurately to a target area.
2. Maneuver within that area to fulfill its mission.
3. Return safely and accurately to its base.

## Overview of the Project
In this project, we are using **Bluetooth wireless technology** to control a robot car. This approach provides a simple and efficient communication system. The remote controller is an Android device with built-in Bluetooth. The user needs to install an application from the following credentials:

- **Google Drive Email**: `allinoneroboticcar@gmail.com`
- **Password**: `AllInOneRoboticCar@123`

Once the application is installed and Bluetooth is enabled on the mobile device, the user can perform various actions.

### Key Features
1. **Basic Movements**:
   - Move Forward
   - Move Backward
   - Turn Left
   - Turn Right
   (Using voice commands, joysticks, switches, or gravity commands)

2. **Advanced Functionalities**:
   - Obstacle Avoidance
   - Line Following
   - Human Following
   - Door Monitoring

These commands are sent from the Android device to the robot car.

### Technology Stack
- **Bluetooth Module**:
  A serial communication medium that connects the robot car to the phone's Bluetooth. This enables wireless communication and command transfer.

- **Arduino UNO**:
  The core of the system, equipped with an **ATMEGA32 microcontroller**, responsible for interpreting commands and controlling the car’s movements. Arduino simplifies converting digital and analog signals into physical movements.

### Why Bluetooth-Based Control?
1. **Wider Range**:
   Bluetooth provides a significant range for controlling the robot car.
2. **Flexibility**:
   - The remote can be changed at any time.
   - Any Android device (phones, tablets, or computers) can be used as the controller.
3. **Efficiency**:
   - Bluetooth communication is reliable and efficient.
4. **Barrier-Free Operation**:
   - Physical barriers like walls and doors do not affect control.

### How to Get the Application
The application required to control the robot car can be downloaded from Google Drive using the following credentials:

- **Email**: `allinoneroboticcar@gmail.com`
- **Password**: `AllInOneRoboticCar@123`

---
With these features and technologies, this project demonstrates a robust and versatile remote-controlled robot car using Bluetooth communication and Arduino.

