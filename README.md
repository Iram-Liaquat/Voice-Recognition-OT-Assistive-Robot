# Voice Recognition based Operation Theatre Assistive Robot

![Status](https://img.shields.io/badge/Status-Educational_Use_Only-blue)
![C++](https://img.shields.io/badge/C++-Arduino-orange.svg)
![Kinematics](https://img.shields.io/badge/Kinematics-RoboAnalyzer-yellow.svg)
![Hardware](https://img.shields.io/badge/Hardware-4DOF_Manipulator-green.svg)

> **B.Sc. Final Year Thesis** | Mechatronics & Control Engineering, UET Lahore (Faisalabad Campus), 2019  
> **Authors**: **Iram Liaquat**, Arslan Ahmed, Amr Fazeel Baig, Samavia Noor  
> **Supervisors**: Engr. Syed Muhammad Umer, Engr. Armaghan Mehmood  

---

## 📖 Abstract
This repository documents the design, fabrication, and kinematic analysis of a **4-DOF articulated assistive robot** tailored for sterile Operation Theatre (OT) environments. The system enables surgeons to request tools hands-free, minimizing contamination risks. 

The architecture integrates a **Geeetech Voice Recognition Module (VRM V3)** for isolated command parsing, an **encoder-feedback elevator mechanism** for precise tray positioning, and a **4-DOF robotic manipulator** executing joint-space trajectories. Upon voice command, the system identifies the tool, positions the respective tray, and utilizes color recognition to detect the surgeon's gloves, successfully completing the pick-and-place cycle in **~8 seconds**.

---

## 🎯 System Architecture & Multi-Modal Sensing
The system is divided into three synchronized subsystems managed by a distributed Arduino architecture (UNO & MEGA):

1. **Voice Command Parsing (UART)**: The Geeetech VRM V3 is trained via `SoftwareSerial` (RX:2, TX:3) to recognize 4 isolated tool commands (Scissor, Knife, Thread, Needle) in a low-noise environment.
2. **Closed-Loop Elevator Actuation**: A DC motor driven by an **L298 H-Bridge** moves the 4-tier tool tray. A **KY-040 Rotary Encoder** (pins 5, 6) provides closed-loop position feedback, ensuring the correct tray aligns with the manipulator's workspace:
   - Scissor: Encoder position `-7`
   - Knife: Encoder position `-48`
   - Thread: Encoder position `-28`
   - Needle: Encoder position `-20`
3. **4-DOF Manipulator Control**: Five **MG996R high-torque servos** (4 for joints, 1 for the rack-and-pinion gripper on pins 6, 7, 8, 9) execute pre-calculated joint-angle trajectories to pick the tool and present it to the surgeon.
4. **Vision-Assisted Handover**: A color sensor mounted below the end-effector detects the specific color of the surgeon's gloves to validate the drop-off zone.

---

## 📐 Kinematic Modeling & Simulation
The manipulator utilizes an **elbow-type articulated configuration**. The forward kinematics were derived using the Denavit-Hartenberg (D-H) convention and validated via **RoboAnalyzer 7** (IIT Delhi).

### Denavit-Hartenberg (D-H) Parameters
| Link ($i$) | $a_i$ (inch) | $\alpha_i$ (deg) | $d_i$ (inch) | $\theta_i$ |
| :---: | :---: | :---: | :---: | :---: |
| **1** | 0 | -90 | $L_1$ (4.2) | $\theta_1^*$ |
| **2** | $L_2$ (9.7) | 0 | 0 | $\theta_2^*$ |
| **3** | $L_3$ (10.4) | 0 | 0 | $\theta_3^*$ |
| **4** | $L_4$ (3.1) | 0 | 0 | $\theta_4^*$ |

* **Forward Kinematics**: Homogeneous transformation matrices ($T^0_4 = T^0_1 T^1_2 T^2_3 T^3_4$) were derived to map joint space to Cartesian space.
* **Inverse Kinematics**: Solved using the geometric approach to determine joint angles for the desired end-effector position $(x, y, z)$.
* **Jacobian Matrix**: A $6 \times 4$ Jacobian was formulated to map joint velocities to end-effector linear/angular velocities and to identify kinematic singularities.

*(Detailed mathematical derivations and RoboAnalyzer simulation graphs are available in the `/docs` folder).*

---

## 🛠️ Hardware Bill of Materials (BOM)
| Component | Specification | Role in System |
| :--- | :--- | :--- |
| **Microcontrollers** | Arduino UNO & Arduino MEGA 2560 | UNO handles VRM UART & Encoder interrupts; MEGA handles 5x PWM Servo control. |
| **Actuators** | 5x MG996R High-Torque Servos + 1x DC Motor | 4-DOF manipulator joints + rack-and-pinion gripper (Servos); Elevator actuation (DC Motor). |
| **Motor Driver** | L298 Dual H-Bridge | Elevator DC motor direction and PWM speed control. |
| **Sensors** | KY-040 Rotary Encoder + Color Sensor | KY-040 provides closed-loop feedback for the elevator; Color sensor detects surgeon's gloves for handover validation. |
| **Voice Module** | Geeetech Voice Recognition Module V3 | Isolated word recognition via UART (`SoftwareSerial`). |
| **Mechanical** | Custom Acrylic/Metal Chassis | 3.2 ft elevator mechanism + 30-inch total length 4-link articulated arm. |

---

## 💻 Code Structure & Logic
The firmware is modularized to prevent blocking operations and ensure real-time responsiveness (based on Appendix C of the thesis):

* **`/firmware/VoiceRecognition.ino`**: Initializes the VRM V3 via `SoftwareSerial`. Loads the 4 voice groups (`onRecord`, `offRecord`, `inRecord`, `outRecord`) into the module's RAM and listens for the `buf[1]` index to trigger the corresponding tool request.
* **`/firmware/ElevatorControl.ino`**: Implements closed-loop control logic using the `Encoder.h` library. It reads KY-040 pulses and drives the L298 motor until the target encoder count is reached (e.g., `if(a == -7)` stops the motor for the Scissor tray).
* **`/firmware/ManipulatorControl.ino`**: Maps the voice triggers (pins 2, 3, 4, 5) to specific joint-space trajectories. It sequentially writes angles to the 4 servos (pins 6, 7, 8, 9) to reach the tray, close the gripper, move to the handover zone, and release.

---

## 📊 Results & Engineering Limitations
* **Performance**: Successfully achieved 4-DOF articulated motion and closed-loop elevator positioning. The end-to-end voice-to-handover cycle was completed in **~8 seconds**.
* **Limitations**: 
  * The Geeetech VRM V3 relies on isolated-word recognition and is highly sensitive to ambient noise (though OT environments are typically controlled
 
---

## 📄 Detailed Documentation
For a deeper dive into the research, methodology, and results, please refer to the comprehensive documents in the `/docs` folder:
- 📊 **[Final Presentation](./docs/FYP_Final_Presentation.pdf)**: A visual walkthrough of the problem statement, hardware architecture, and prototype demonstration.
- 📐 **[D-H Kinematics Derivation](./docs/DH_Kinematics_Derivation.md)**: Complete D-H parameter tables, transformation matrices, and inverse kinematics.
- 📉 **[Jacobian & Singularity Analysis](./docs/Jacobian_and_Singularity_Analysis.md)**: Differential kinematics and workspace singularity identification.
- ⚙️ **[Hardware Design Document](./docs/Hardware_Design_Document.md)**: Complete BOM, pin mappings, and mechanical specifications.
- 🏗️ **[System Architecture](./docs/System_Architecture.md)**: Block diagrams, data flow, and communication protocols.
- 🖼️ **[System Diagrams](./docs/System_Diagram.md)**: High-level visual architecture and block diagrams.

---

## 👥 Team Project & Technical Focus
This was a collaborative 4-person B.Sc. thesis project. While the workload was distributed across the team (covering mechanical design, CAD, and firmware), my technical focus and foundational learning in this project centered on:

- **Kinematic Modeling & Simulation**: Utilizing Denavit-Hartenberg (D-H) parameters and RoboAnalyzer to derive forward kinematics and validate the 4-DOF manipulator's workspace and trajectory planning.
- **Hardware-Software Integration**: Bridging the communication between the Geeetech Voice Recognition Module (UART), the KY-040 encoder feedback loop, and the Arduino-based servo control system.
- **System-Level Validation**: Testing the end-to-end "voice-to-handover" pipeline, troubleshooting friction factors, and ensuring the 8-second cycle time met the operational requirements for a sterile environment.

*This project served as my foundational introduction to robotics and embedded system validation, directly inspiring my current 5+ year career in Embedded QA and safety-critical system testing.*

---

## 📂 Repository Structure
```text
├── /assets                 # System demonstration GIF
├── /docs                   # Final Presentation, D-H derivations, Jacobian analysis, Hardware specs, System Architecture & Diagram
├── /firmware               # Modular Arduino C++ code (Voice, Elevator, Manipulator)
└── README.md               # Main project documentation
