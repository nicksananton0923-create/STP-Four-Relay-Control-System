# STP Four-Relay Control System

## Table of Contents
1. [Project Purpose](#1-project-purpose)
2. [Problem Statement](#2-problem-statement)
3. [Project Objectives](#3-project-objectives)
4. [Current Project Status](#4-current-project-status)
5. [Confirmed Technologies and Components](#5-confirmed-technologies-and-components)
6. [Proposed Components](#6-proposed-components)
7. [System Operation](#7-system-operation)
8. [Architecture or Workflow](#8-architecture-or-workflow)
9. [Installation or Setup Instructions](#9-installation-or-setup-instructions)
10. [Testing Status](#10-testing-status)
11. [Safety Considerations](#11-safety-considerations)
12. [Known Limitations](#12-known-limitations)
13. [Future Improvements](#13-future-improvements)
14. [Repository Structure](#14-repository-structure)
15. [Licence Information](#15-licence-information)
16. [Status Label Convention](#16-status-label-convention)

## 1. Project Purpose

This project provides a programmable four-relay controller intended for use in a Sewage Treatment Plant (STP) process tank. The controller drives four independent loads — Blower 1, the MBBR (Moving Bed Biofilm Reactor) aeration unit, the Sludge system, and Blower 2 — through a four-channel relay module controlled by an Arduino Uno. The project documents the control concept, the proposed hardware, and a configurable firmware starting point that the original designer can adapt to match their actual plant sequencing requirements. The package is intended to support education, documentation, and continued development rather than immediate deployment.

## 2. Problem Statement

STP process tanks require coordinated operation of multiple aeration and sludge-handling loads to maintain dissolved oxygen levels, support biofilm growth in MBBR stages, and prevent sludge accumulation. Manual control of these loads is labour-intensive and inconsistent, while commercial PLC-based controllers are expensive for small-scale or educational plants. A simple, configurable Arduino-based four-relay controller fills the gap between manual operation and a full industrial automation system, providing repeatable timed sequencing with clear operator diagnostics. The trade-off is that such a controller is not a substitute for a certified industrial controller in regulated or mission-critical applications.

## 3. Project Objectives

- Document a four-relay STP load control concept with clear status labelling.
- Provide a compilable Arduino Uno sketch as a starting point for the original designer.
- Include a configurable timing cycle for Blower 1, MBBR, Sludge system, and Blower 2.
- Document electrical isolation, contactor interfaces, and protection requirements.
- Clearly label all pin assignments as NOT VERIFIED pending confirmation against the original sketch.
- Provide test, safety, and limitations documentation suitable for portfolio use.

## 4. Current Project Status

| Item | Status |
|---|---|
| Arduino Uno as main controller | PROPOSED |
| 4-channel relay module | PROPOSED |
| Four loads (Blower 1, MBBR, Sludge, Blower 2) | PROPOSED |
| Pin assignments | NOT VERIFIED |
| Contactor / isolation interfaces | PROPOSED |
| Firmware starting point | IMPLEMENTED (in `src/`) |
| Hardware build | NOT VERIFIED |
| Physical testing | NOT YET TESTED |

## 5. Confirmed Technologies and Components

No hardware has been confirmed against an inspected original sketch. All technologies listed in this README are PROPOSED and require verification before any physical build. The following technologies are proposed for the controller:

- Arduino Uno (ATmega328P, 5 V logic)
- 4-channel active-low relay module with optocoupler isolation
- Four independent contactors (one per load) for mains-side switching
- 24 V DC or 230 V AC control circuits depending on contactor coil rating
- Regulated 5 V supply for the Arduino and relay module

Because no original sketch has been inspected for this portfolio entry, none of the above can be marked CONFIRMED. Any pin number that appears later in this README or in the source code is a placeholder pending confirmation against the original design.

## 6. Proposed Components

| Component | Role | Notes |
|---|---|---|
| Arduino Uno R3 | Main controller | 5 V logic, 14 digital I/O, 6 analog |
| 4-channel relay module (optocoupler-isolated) | Switches 4 independent loads | Active-low trigger assumed; verify against module |
| Contactor x4 (one per load) | Mains-side load switching | Coil voltage and current rating must match the load; consult load datasheet |
| Flyback diodes / RC snubbers | Inductive load protection | One per contactor coil |
| 5 V DC regulated supply | Arduino + relay module power | Separate from mains; verify current rating ≥ total relay coil current |
| DIN-rail enclosure, IP54+ | Cabinet protection | Required for STP plant environment |
| Manual override switches | Operator bypass | Recommended for maintenance |
| EPO (Emergency Power Off) button | Safety cut-off | Mandatory for any motor control cabinet |

## 7. System Operation

The proposed control sequence operates the four loads in a configurable cycle. Each load has an ON duration and an OFF duration, and the loads are sequenced rather than all switched simultaneously, to limit inrush current and distribute aeration effort across the process tank. The exact timing values are intentionally left as configurable parameters in the firmware so that the original designer can match the values to the actual plant's biological process requirements. Typical STP aeration cycles alternate between an aeration phase (blowers ON, MBBR mixing active) and a settling phase (sludge system operational, blowers OFF). The firmware implements a simple state machine that cycles through these phases. A Serial Monitor interface is provided for basic diagnostics: current state, time elapsed in current state, and next state. The state machine is intentionally simple — it does not include dissolved oxygen feedback, remote monitoring, or PID control — to keep the starting point approachable for educational use and further development.

## 8. Architecture or Workflow

The system architecture follows a layered isolation pattern that is standard practice for low-voltage control of mains-powered loads. The Arduino Uno operates at 5 V logic and drives four digital outputs to the input side of a 4-channel relay module. The relay module uses optocouplers to provide galvanic isolation between the Arduino and the relay coils. The relay outputs switch the coils of four independent contactors, which in turn switch the mains supply to each load. This double-isolation pattern (optocoupler + contactor) is recommended for any application where a low-voltage controller switches mains-powered motors, because it protects the Arduino from back-EMF, ground loops, and accidental mains contact. The proposed block diagram is:

```
[Arduino Uno] --GPIO--> [4-ch Relay Module (opto)] --dry contact--> [Contactor coil]
                                                                      |
                                                                      v
                                                                  [Mains Load]
```

Power supply architecture: a single mains input feeds a 5 V DC regulated supply for the Arduino and relay module, and a separate mains feed (via the contactors) feeds the loads. The two supplies are galvanically separated and should be wired in separate conduits or cable trays within the enclosure.

## 9. Installation or Setup Instructions

The firmware can be compiled and uploaded using the Arduino IDE without third-party libraries. Steps:

1. Open `src/stp_four_relay_control.ino` in the Arduino IDE.
2. Select **Tools → Board → Arduino Uno**.
3. Select the correct COM port.
4. Edit the pin assignments at the top of the sketch — the defaults are placeholders and must be confirmed against the original design before wiring.
5. Edit the cycle timing parameters (`BLOWER1_ON_MS`, `MBBR_ON_MS`, etc.) to match the plant's process requirements.
6. Upload the sketch.
7. Open the Serial Monitor at 9600 baud to view state diagnostics.
8. Before connecting any load, dry-run the relay module and confirm each channel actuates at the expected state transition.

Hardware setup must only be performed by a person competent to work with mains voltage. The enclosure must be rated for the environment (IP54 minimum for an STP plant cabinet). All mains wiring must be fused, earthed, and labelled.

## 10. Testing Status

All tests are currently **NOT YET TESTED**. No physical test has been performed on this package. The following tests are defined in `docs/testing-and-validation.md` and must be performed before any deployment:

1. Firmware compile test (Arduino IDE)
2. Dry-run relay actuation test (no load connected)
3. Continuity and isolation test (mains wiring)
4. Load current measurement at each contactor
5. Endurance test of the cycle for ≥ 24 hours
6. Thermal inspection of the enclosure under load

11. Safety Considerations

This project involves mains-voltage switching of inductive motor loads. The following safety considerations are mandatory and not optional:

- **Mains isolation:** All mains wiring must be carried out by a qualified person. Low-voltage (Arduino) and mains (contactor) wiring must be in separate conduits and physically separated within the enclosure.
- **Earth leakage protection:** A residual current device (RCD / GFCI) must protect the mains feed to the enclosure.
- **Overcurrent protection:** Each load circuit must have its own appropriately-rated fuse or miniature circuit breaker (MCB).
- **Inductive load protection:** Each contactor coil must have a flyback diode (DC coil) or RC snubber (AC coil) to suppress back-EMF when the relay opens.
- **Lockout-tagout (LOTO):** A physical lockable isolator must be fitted upstream of the enclosure so that maintenance can be performed safely.
- **Emergency Power Off (EPO):** An EPO button must cut all mains power to the enclosure and must be wired independently of the Arduino.
- **Enclosure rating:** IP54 minimum for an STP plant environment, with appropriate ventilation for heat dissipation.
- **No live working:** All wiring changes must be made with the mains supply fully isolated and verified dead.

This project is not a certified industrial controller. It is an educational and documentation package. Use in a real plant requires engineering review by a competent person and compliance with local electrical codes.

 12. Known Limitations

- The firmware is a starting point only. It does not include feedback control, dissolved oxygen sensing, or remote monitoring.
- Pin assignments are NOT VERIFIED against the original sketch and must be confirmed before wiring.
- Timing values are configurable placeholders, not validated process parameters.
- No PID control is implemented; all switching is time-based.
- No data logging is implemented; cycle history is not retained across power cycles.
- The firmware does not handle sensor faults or communication failures because no sensors are used in this starting version.
- Single-board reliability: an Arduino Uno is not a SIL-rated controller and is not suitable as the sole controller for a critical wastewater process.

 13. Future Improvements

- Add a real-time clock (RTC, e.g. DS3231) for accurate timed scheduling across power cycles.
- Add a dissolved oxygen (DO) sensor input and switch to feedback-based aeration control.
- Add Modbus RTU over RS-485 for SCADA integration.
- Add an SD card data logger for cycle history.
- Add a local HMI (e.g. 16x2 LCD or 20x4 LCD with keypad) for operator interaction.
- Add a watchdog timer and brown-out detection for firmware robustness.
- Migrate to an industrial-grade controller (e.g. industrial Arduino or PLC) for production deployment.

 14. Repository Structure

```
04-stp-four-relay-control/
├── README.md
├── LICENSE
├── docs/
│   ├── project-overview.md
│   ├── requirements.md
│   ├── system-architecture.md
│   ├── logic-and-operation.md
│   ├── components-and-bill-of-materials.md
│   ├── wiring-and-connections.md
│   ├── testing-and-validation.md
│   ├── safety-considerations.md
│   ├── development-roadmap.md
│   └── limitations.md
└── src/
    └── stp_four_relay_control.ino
```

 15. Licence Information

Released under the MIT Licence. See the `LICENSE` file for the full text.

 16. Status Label Convention

This project uses the following status labels throughout its documentation. Each label has a strict meaning and is not used interchangeably with any other label.

| Label | Meaning |
|---|---|
| **CONFIRMED** | Directly supported by available project information or inspected source code. |
| **PROPOSED** | A suggested design or implementation. Has not been verified against built hardware. |
| **NOT VERIFIED** | Information that has not been confirmed. Requires verification before use. |
| **IMPLEMENTED** | A feature or system that has actually been created and exists in the source code. |
| **TESTED** | A test that has genuinely been performed with recorded results. |
| **NOT YET TESTED** | Code, hardware, or functionality that still requires testing. |

If a section does not carry any status label, the content of that section is informational prose and does not make a claim of verification, testing, or implementation.
