# Development Roadmap — STP Four-Relay Control System

## v1.0 (current — PROPOSED starting point)

- Four-relay state machine with configurable timings
- Serial Monitor diagnostics
- Power-on safe state
- Documentation package

## v1.1 (planned)

- Add a real-time clock (DS3231) for accurate timed scheduling across power cycles.
- Add an SD card data logger to record cycle history.
- Add a watchdog timer for firmware robustness.
- Add brown-out detection.

## v1.2 (planned)

- Add a 16x2 or 20x4 LCD with keypad for local HMI.
- Add hardware pause and reset buttons.
- Add a status LED per load.

## v2.0 (planned)

- Add a dissolved oxygen (DO) sensor input.
- Switch from time-based control to feedback control (aeration driven by DO setpoint).
- Add a turbidity sensor for the sludge system.

## v2.1 (planned)

- Add Modbus RTU over RS-485 for SCADA integration.
- Add Ethernet or Wi-Fi for remote monitoring (would require migration to a more capable controller such as an ESP32 or an industrial Arduino).

## v3.0 (future)

- Migrate to a SIL-rated industrial controller (PLC or safety-rated Arduino) for production deployment.
- Add redundant power supplies.
- Add UPS for ride-through during short mains interruptions.
- Add remote firmware update capability with cryptographic verification.

## Migration Path

The v1.x → v2.x migration path replaces the simple time-based state machine with a feedback-based controller. The v2.x → v3.x migration path replaces the Arduino-class controller with an industrial-grade controller. Each migration should preserve the existing documentation and add a new section explaining the migration rationale, the new hardware, and any changes to the control logic.
