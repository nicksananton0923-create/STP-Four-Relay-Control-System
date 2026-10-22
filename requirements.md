# Requirements — STP Four-Relay Control System

## Functional Requirements

| ID | Requirement | Status |
|---|---|---|
| FR-01 | The controller shall drive four independent loads via a 4-channel relay module. | PROPOSED |
| FR-02 | The controller shall sequence the four loads in a configurable ON/OFF cycle. | PROPOSED |
| FR-03 | Each load shall have independently configurable ON duration and OFF duration. | PROPOSED |
| FR-04 | The controller shall report current state, elapsed time, and next state via Serial Monitor. | IMPLEMENTED |
| FR-05 | The controller shall enter a known safe state (all relays OFF) on power-on. | IMPLEMENTED |
| FR-06 | The controller shall provide a configurable cycle start delay to limit inrush current. | PROPOSED |

## Non-Functional Requirements

| ID | Requirement | Status |
|---|---|---|
| NFR-01 | The firmware shall compile on a stock Arduino Uno without third-party libraries. | IMPLEMENTED |
| NFR-02 | The enclosure shall be rated IP54 or better for an STP plant environment. | PROPOSED |
| NFR-03 | Each mains load circuit shall be independently fused. | PROPOSED |
| NFR-04 | The controller shall provide galvanic isolation between low-voltage logic and mains circuits. | PROPOSED |
| NFR-05 | The enclosure shall include a lockable upstream isolator for lockout-tagout. | PROPOSED |

## Out-of-Scope

The following items are explicitly out of scope for this version and are listed for future work:

- Dissolved oxygen (DO) sensor feedback control
- SCADA / Modbus integration
- SD card data logging
- Real-time clock (RTC) scheduling across power cycles
- PID control of any load
- Remote monitoring via Ethernet or Wi-Fi
- Compliance certification for any specific jurisdiction

## Assumptions

- The four loads are mains-powered and switched via contactors driven by the relay module.
- The plant's biological process requirements (aeration duration, settling duration, sludge wasting frequency) are determined by the original designer and reflected as configurable parameters in the firmware.
- The enclosure is installed in a location accessible to qualified maintenance personnel only.
