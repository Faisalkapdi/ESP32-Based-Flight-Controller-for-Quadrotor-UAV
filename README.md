# ESP32-Based-Flight-Controller-for-Quadrotor-UAV

An ESP32-based flight controller developed for quadrotor UAVs, featuring real-time attitude stabilization, wireless telemetry, GPS-ready architecture, and a modular embedded software framework.

The project was built to understand and implement the core technologies behind modern flight controllers, including sensor interfacing, control systems, navigation, and real-time embedded programming.

---
https://github.com/user-attachments/assets/edf892ee-bebb-429e-b02c-eb0a28ddc0f8

# Project Overview

This project presents the design, development, and performance evaluation of a custom flight controller for a quadrotor unmanned aerial vehicle (UAV). The system is developed around the ESP32 microcontroller and integrates sensor fusion, cascaded PID control, telemetry communication, and real-time flight stabilization.

The primary objective of this work is to create a low-cost, open-source, and educational flight control platform that enables students and researchers to understand the internal working of modern drone systems while providing reliable flight performance.

The developed controller performs real-time attitude estimation, flight stabilization, motor control, wireless telemetry, and future autonomous navigation support.

---

# What Makes This Project Different?

Most student drone projects rely entirely on ready-made flight controllers such as Pixhawk or Betaflight boards. In this project, the control system itself was designed and implemented from scratch, allowing complete control over sensor processing, flight logic, and system behavior.

The project demonstrates how a low-cost ESP32 can be transformed into a capable UAV flight controller while providing a deeper understanding of embedded systems, control engineering, and autonomous aerial vehicles.

---

# Key Features

* ESP32-based flight control system
* Cascaded PID control architecture
* Real-time attitude stabilization
* MPU6050 inertial measurement unit integration
* GPS and barometric sensor support
* Wireless telemetry communication
* Battery monitoring and safety management
* Modular firmware architecture
* Open-source development platform

---

# Hardware Components

| Component             | Description               |
| --------------------- | ------------------------- |
| ESP32 Dev Board       | Main Controller           |
| MPU6050               | Accelerometer + Gyroscope |
| BMP280                | Altitude Measurement      |
| NEO-M8N GPS           | Position Tracking         |
| NRF24L01              | Wireless Telemetry        |
| A2212 1400KV Motors   | Propulsion System         |
| SimonK 30A ESC        | Motor Speed Control       |
| F450 Frame            | Drone Structure           |
| 2200mAh Li-Po Battery | Power Source              |
| FlySky FS-i6X         | Remote Controller         |

---

# Flight Control Algorithm
<img width="1179" height="1038" alt="WhatsApp Image 2026-06-06 at 12 21 13 AM (1)" src="https://github.com/user-attachments/assets/7175c1ad-f31d-4a6c-b17e-c9e07ca575da" />

Signals: θre f = angle setpoint (deg), eθ = angle error, ωsp = rate setpoint, eω = rate error, u = control
output, ω = angular rate, θˆ = estimated angle.

## Cascaded PID Control

The control architecture uses two feedback loops:

### Outer Loop (Angle Controller)

* Maintains desired roll and pitch angles
* Generates angular rate commands
* Provides self-leveling behavior

### Inner Loop (Rate Controller)

* Uses gyroscope feedback
* Controls angular velocity
* Ensures rapid stabilization

A complementary filter combines accelerometer and gyroscope measurements to provide accurate attitude estimation for stable flight control.

The controller operates at:

**250 Hz Control Frequency**

---

# Stability Analysis

Extensive mathematical and practical validation was carried out.

## Final PID Parameters

| Parameter | Value |
| --------- | ----- |
| Kp        | 0.40  |
| Ki        | 0.20  |
| Kd        | 0.03  |

## Angle Controller Parameters

| Parameter | Value |
| --------- | ----- |
| Kp Angle  | 5.0   |
| Ki Angle  | 0.5   |

The obtained results confirm stable flight operation with excellent disturbance rejection and fast response characteristics.

---

## Web-Based Ground Control Station

<img width="508" height="595" alt="WhatsApp Image 2026-06-06 at 12 21 20 AM" src="https://github.com/user-attachments/assets/2f65efe6-3724-4115-9d01-3b9b8a0f825f" />


The flight controller hosts a lightweight web-based Ground Control Station (GCS) through the ESP32's integrated Wi-Fi capability. This interface allows real-time monitoring of flight parameters and controller tuning without requiring additional desktop software.

### Features

- Real-time Roll and Pitch monitoring
- Target Angle and Actual Angle visualization
- Angular Rate monitoring
- Battery voltage display
- Altitude monitoring using Barometer and Laser data
- Live PID tuning for Roll, Pitch, and Yaw controllers
- Angle controller parameter adjustment
- IMU recalibration support
- Blackbox log download
- System status monitoring (Armed/Disarmed)

The dashboard simplifies controller tuning and testing by providing direct access to critical flight parameters through any web browser connected to the ESP32 network.

---

# Applications

* UAV Research and Development
* Autonomous Drone Platforms
* Educational Flight Control Systems
* Precision Agriculture
* Infrastructure Inspection
* Environmental Monitoring
* Surveillance and Mapping
* IoT-Based Aerial Systems

---

# Repository Contents

```text
src/            → Main flight control firmware
lib/            → Drivers and control modules
docs/           → Project documentation
hardware/       → Circuit and hardware design files
images/         → Project images and diagrams
README.md       → Project documentation
```

---

# License

This project is intended for educational, research, and non-commercial purposes. Users are encouraged to study, modify, and extend the system while providing appropriate credit to the original contributors.

