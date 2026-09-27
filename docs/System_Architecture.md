# System Architecture & Technical Specifications: OTAR

This document details the hardware specifications, distributed control subsystems, operational workflow, and communication protocols of the 4-DOF Operation Theatre Assistive Robot (OTAR).

**Supervisor:** Engr. Syed Muhammad Umer  
**Team:** Iram Liaquat, Amr Rauf, Arslan Ahmed, Samavia Noor

---

## 1. Project Specifications & Hardware

The mechanical design was driven by ergonomic guidelines for general surgical procedures and required workspace dimensions.

| Specification | Value / Dimension |
| :--- | :--- |
| **Workspace Dimensions** | 1.5 x 1.5 ft |
| **Operating Table Height** | 2.0 - 2.5 ft |
| **Elevator Height / Width** | 3.2 ft / 1.3 ft |
| **Elevator Gears (Top / Bottom)**| 19 cm / 8 cm |
| **Total Manipulator Length** | 2.5 ft |
| **Payload Capacity** | 250 g |

### Core Hardware & Algorithms
* **Hardware Modules:** Geeetech Voice Recognition Module, Color Sensor V1.1, MG-996R High-Torque Servos, Encoded DC Motor, Arduino UNO, and Arduino MEGA.
* **Circuit Design:** Custom converter circuit design for stable voltage regulation during multi-servo actuation.
* **System Algorithms:** Voice Recognition (Isolated-word), Manipulator (Joint-space trajectory), Hand Detection (Color-based), and Elevator Mechanism (Closed-loop feedback).

---

## 2. Core Subsystems & Control Flow

| Subsystem | Components | Function |
| :--- | :--- | :--- |
| **Sensing** | Geeetech VRM V3, KY-040 Encoder, Color Sensor V1.1 | Parses isolated voice commands, provides closed-loop elevator feedback, and validates surgeon hand presence. |
| **Processing** | Arduino UNO, Arduino MEGA 2560 | **UNO:** Handles UART, encoder interrupts, and elevator logic. **MEGA:** Generates precise 50Hz PWM for 5 servos. |
| **Actuation** | Encoded DC Motor, 5x MG996R Servos, L298 Driver | Drives the 4-tier elevator tray and executes 4-DOF joint-space trajectories + rack-and-pinion gripper. |
| **Power** | Custom Converter Circuit | Regulates voltage to prevent microcontroller brownouts during simultaneous multi-servo stall currents. |

---

## 3. Operational Workflow (Methodology)

The system executes a synchronized, sequential pick-and-place cycle as defined in the project methodology:

1. **Voice Trigger:** Recognizing the voice command of the surgeon.
2. **Simultaneous Movement:** Manipulator and elevator move simultaneously to the target coordinates.
3. **Tool Acquisition:** Picking the requested surgical tool using the rack-and-pinion gripper.
4. **Hand Detection:** Validating the drop-off zone via color recognition of the surgeon's gloves.
5. **Tool Release:** Releasing the tool safely into the surgeon's hand.
6. **Reset:** Returning to the initial home position.

---

## 4. Communication Protocols & Pin Mapping

| Interface | Protocol | Source | Destination | Purpose |
| :--- | :--- | :--- | :--- | :--- |
| **VRM to UNO** | UART (`SoftwareSerial`) | VRM V3 | UNO (Pins 2, 3) | Transmit recognized voice index. |
| **UNO to MEGA** | Digital I/O (Binary) | UNO (Pins 11, 12) | MEGA (Pins 2-5) | Trigger specific arm trajectories. |
| **Encoder to UNO** | Quadrature Pulse | KY-040 | UNO (Pins 5, 6) | Closed-loop elevator position. |
| **MEGA to Servos** | PWM (50Hz) | MEGA (Pins 6-9) | MG996R Servos | Joint angle and gripper control. |
| **UNO to Motor** | PWM & Logic | UNO | L298 Driver | Elevator speed and direction. |

---

##  References

| # | Citation | Context |
| :---: | :--- | :--- |
| **[1]** | Parnab, Vijay (2015). *Voice recognition: Speech to text*. | Voice Module Baseline |
| **[2]** | Elias Eliot, Deepak (2015). *Design and kinematic analysis of articulated manipulator*. | Manipulator Kinematics |
| **[3]** | Ivan, Arkady, Pavel (2017). *Development of Dual arm assistant robot*. | Multi-Arm Control Systems |
| **[4]** | Virendra, Ritu (2016). *Survey of Robotic arm and Parameters*. | Arm Parameter Selection |
| **[5]** | Mary, Sudharshan (2018). *Color detection in RGB modeled images using MATLAB*. | Hand Detection Algorithm |
| **[6]** | Azimuddin, A. F., et al. (2017). *Ergonomic assessment of operating table heights*. | Workspace Ergonomics |
