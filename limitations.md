# Limitations — STP Four-Relay Control System

## Hardware Limitations

- **Pin assignments are NOT VERIFIED.** The default pin assignments in the firmware are placeholders and must be confirmed against the original design before any wiring is connected. Using the wrong pin assignment can damage the Arduino, the relay module, or the loads.
- **Relay module type is assumed, not confirmed.** The firmware assumes an active-low relay module. If the module is active-high, the relay behaviour will be inverted (relays energised when the firmware says they should be OFF and vice versa). This is a safety hazard and must be verified before any load is connected.
- **No contactor ratings are confirmed.** The contactor ratings shown in the BOM are typical values. The actual ratings must be selected based on each load's full-load current, inrush current, and duty cycle.
- **No environmental rating is confirmed.** The IP54 minimum is a recommendation; the actual enclosure rating must be selected for the specific installation environment.
- **No redundancy.** The controller has a single Arduino, a single relay module, and a single power supply. A failure of any of these will stop the controller. This is acceptable for an educational or small-scale plant but is not acceptable for a critical wastewater process.

## Firmware Limitations

- **Time-based control only.** The firmware does not use sensor feedback. If the plant's biological process requirements change, the timings must be manually updated.
- **No real-time clock.** Cycle timing is based on the Arduino's `millis()` function, which is not accurate across power cycles and drifts over time.
- **No data logging.** Cycle history is not retained. If the Arduino resets, the cycle count is lost.
- **No remote monitoring.** The controller has no communication interface. All diagnostics are local via the Serial Monitor.
- **No fault detection.** The firmware does not detect stuck relays, open contactor coils, or load failures.
- **Single-threaded.** The state machine is a single loop. Long-running operations block other tasks.

## Documentation Limitations

- **No original sketch has been inspected.** The firmware is a fresh starting point, not a preservation of an existing design. Any pin assignment, timing value, or logic flow that matches the original design is coincidental and must be confirmed by the original designer.
- **No measured values.** All current, voltage, and timing values in the documentation are typical or recommended values, not measured values from a built system.
- **No test results.** All tests are NOT YET TESTED.

## Scope Limitations

This package does not cover:
- Biological process design of the STP
- Sizing of blowers, MBBR media, or sludge pumps
- Piping and instrumentation diagrams (P&ID) for the plant
- Regulatory compliance for wastewater discharge
- Operator training
- Maintenance procedures for the loads themselves

These items are out of scope and are the responsibility of the plant designer and operator.

## Reliability Limitations

The Arduino Uno is an educational development board, not an industrial controller. Its limitations include:

- No SIL (Safety Integrity Level) rating
- Limited ESD protection on GPIO pins
- Limited EMC immunity
- No redundancy
- Single point of failure on the microcontroller
- Limited operating temperature range (typically 0 °C to +50 °C commercial grade)

For a production STP plant, a SIL-rated industrial controller (PLC or safety-rated Arduino variant) is recommended. The v3.0 roadmap item addresses this migration.
