# Hardware Design & System Specifications

This document details the electrical, electronic, and mechanical design specifications of the 4-DOF Operation Theatre Assistive Robot. All component selections and dimensions are based on the final fabricated prototype and kinematic workspace requirements.

---

## 1. Bill of Materials (BOM)

| Component | Specification | Role in System |
| :--- | :--- | :--- |
| **Microcontrollers** | **Arduino UNO** (ATmega328P, 16MHz, 5V)<br>**Arduino MEGA 2560** (ATmega2560, 16MHz, 5V) | UNO handles Voice Module UART & Encoder interrupts. MEGA handles 5x PWM Servo control due to higher I/O capacity. |
| **Actuators** | **5x MG996R High-Torque Digital Servos**<br>(4.8V/6.0V, ~9.4 kgf.cm stall torque, metal gearing, 0.17s/60° speed) | 4 for manipulator joints (Base, Shoulder, Elbow, Wrist) + 1 for the rack-and-pinion gripper. |
| **Elevator Motor** | **1x Encoded DC Motor** | Drives the 4-tier surgical tool tray via gear mechanism. |
| **Motor Driver** | **L298 Dual H-Bridge**<br>(Up to 40V, 4A DC, over-temp protection) | Controls elevator DC motor direction and PWM speed. |
| **Position Sensor** | **KY-040 Rotary Encoder**<br>(5V, 20 pulses/circle) | Provides closed-loop position feedback for the elevator mechanism. |
| **Vision Sensor** | **Color Sensor V1.1** | Mounted below the end-effector to detect the specific color of the surgeon's gloves for handover validation. |
| **Voice Module** | **Geeetech Voice Recognition Module V3**<br>(4.5-5.5V, <40mA, 5V TTL UART) | Isolated word recognition (Scissor, Knife, Thread, Needle) with 99% accuracy in low-noise environments. |
| **Mechanical Chassis** | Custom Acrylic/Metal Fabrication | 3.2 ft elevator mechanism + 30-inch (2.5 ft) total length 4-link articulated arm. |

---

## 2. Pin Mapping & Wiring Configuration

To ensure modularity and prevent signal interference, the system utilizes a distributed architecture across two microcontrollers.

### Arduino UNO (Control & Sensing Hub)
| Component | UNO Pin | Purpose |
| :--- | :---: | :--- |
| Geeetech VRM (TX) | Pin 2 | `SoftwareSerial` RX |
| Geeetech VRM (RX) | Pin 3 | `SoftwareSerial` TX |
| KY-040 Encoder (CLK) | Pin 5 | Interrupt-capable encoder pulse reading |
| KY-040 Encoder (DT) | Pin 6 | Interrupt-capable encoder direction reading |
| Limit Sensor | Pin 8 | Elevator bottom limit switch input |
| Trigger Output 1 | Pin 11 | Signal to MEGA (Tool 1 / Tool 3) |
| Trigger Output 2 | Pin 12 | Signal to MEGA (Tool 2 / Tool 4) |

### Arduino MEGA 2560 (Actuation Hub)
| Component | MEGA Pin | Purpose |
| :--- | :---: | :--- |
| Servo 1 (Base) | Pin 6 | PWM control for joint 1 |
| Servo 2 (Shoulder) | Pin 7 | PWM control for joint 2 |
| Servo 3 (Elbow) | Pin 8 | PWM control for joint 3 |
| Servo 4 (Wrist/Gripper)| Pin 9 | PWM control for joint 4 + rack-and-pinion actuation |
| Trigger Input 1 | Pin 2 | Receives signal from UNO |
| Trigger Input 2 | Pin 3 | Receives signal from UNO |
| Trigger Input 3 | Pin 4 | Receives signal from UNO |
| Trigger Input 4 | Pin 5 | Receives signal from UNO |

---

## 3. Mechanical Specifications & Workspace Ergonomics

The mechanical design was driven by ergonomic guidelines for seated general surgical procedures and the required planar workspace.

* **Operating Table Height:** 2.08 ft to 2.5 ft (based on 95th percentile average male height of 5.57 ft and torso length of 1.54 ft).
* **Planar Workspace:** 1.5 ft × 1.5 ft.
* **Total Manipulator Length:** 30 inches (2.5 ft).
* **Payload Capacity:** ~250 grams (sufficient for standard surgical tools like scissors, forceps, and needle holders).

### Elevator Mechanism Dimensions
* **Total Height:** 3.2 ft
* **Width:** 1.31 ft
* **Top Gear Diameter:** 19 cm
* **Bottom Gear Diameter:** 8 cm
* **Drive Rod Diameter:** 1 cm

---

## 4. Power & Safety Considerations

1. **Servo Current Draw:** The MG996R servos can draw up to 2.5A under stall conditions. The Arduino MEGA's 5V pin cannot supply this. An external, regulated 5V/3A+ power supply is required for the servo bus, with a common ground shared with the MEGA.
2. **L298 Voltage Drop:** The L298 driver has an inherent ~2V voltage drop. To achieve optimal DC motor speed for the elevator, a 9V-12V external supply is recommended for the driver's `VCC`/`VM` input.
3. **Voice Module Sensitivity:** The Geeetech VRM V3 requires a low-noise environment (<40dB) for its 99% recognition accuracy. This aligns perfectly with the controlled, quiet environment of a standard Operation Theatre.

---

## 📚 References
1. A. F. Baig, A. Ahmed, I. Liaquat, and S. Noor, "Voice Recognition based Operation Theatre Assistive Robot," B.Sc. Thesis, Dept. of Mechatronics and Control Engineering, UET Lahore (FSD Campus), 2019. *(See Chapter 3: Hardware Design & Appendix A: Data Sheets)*.
