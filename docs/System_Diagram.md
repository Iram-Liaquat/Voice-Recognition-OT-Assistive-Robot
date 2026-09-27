# System Diagram & Data Flow: OTAR

This document provides the high-level architectural block diagram and references to the visual design assets for the Operation Theatre Assistive Robot.

---

## High-Level System Block Diagram

The system utilizes a dual-microcontroller architecture to isolate heavy UART/encoder interrupts from high-frequency PWM servo control.

```text
[ SURGEON ] ──(Voice)──> [ Geeetech VRM V3 ] ──(UART)──> [ ARDUINO UNO ] <──(Pulses)── [ KY-040 Encoder ]
                               │                               │      │
                               │                               │      └──(Digital Triggers)──┐
                               │                               ▼                             │
                               │                       [ L298 H-Bridge ]                     │
                               │                               │                             ▼
                               │                       [ DC Elevator Motor ]       [ ARDUINO MEGA 2560 ]
                               │                                                             │
                               │                                                             ▼
                               │                                                     [ 5x MG996R Servos ]
                               │                                                     (4-DOF Arm + Gripper)
                               │                                                             │
                               ─────────────────────────────────────────────────────────────┘
                                          (Color Sensor V1.1 validates handover zone)
