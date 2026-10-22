# Testing and Validation — STP Four-Relay Control System

## Test Status Summary

| Test ID | Test | Status | Performed by | Date |
|---|---|---|---|---|
| T-01 | Firmware compile test | NOT YET TESTED | — | — |
| T-02 | Dry-run relay actuation test | NOT YET TESTED | — | — |
| T-03 | Continuity and isolation test | NOT YET TESTED | — | — |
| T-04 | Load current measurement | NOT YET TESTED | — | — |
| T-05 | 24-hour endurance test | NOT YET TESTED | — | — |
| T-06 | Thermal inspection under load | NOT YET TESTED | — | — |
| T-07 | Manual override function test | NOT YET TESTED | — | — |
| T-08 | EPO function test | NOT YET TESTED | — | — |

No test has been performed on this package. The tests below are defined as a plan and must be executed before any deployment. Results must be recorded in this file with the actual measured values, the tester's name, and the date.

## Test Procedures

### T-01 Firmware Compile Test
1. Open `src/stp_four_relay_control.ino` in the Arduino IDE.
2. Select **Tools → Board → Arduino Uno**.
3. Click **Verify/Compile**.
4. **Pass criterion:** compilation completes with no errors and no warnings.
5. Record the IDE version and the compilation time.

### T-02 Dry-Run Relay Actuation Test
1. Upload the firmware to the Arduino Uno.
2. Connect the 4-channel relay module to the Arduino per the wiring table.
3. Do NOT connect any load to the relay outputs.
4. Open the Serial Monitor at 9600 baud.
5. Observe one full cycle through `STATE_BLOWER1` → `STATE_MBBR` → `STATE_SLUDGE` → `STATE_BLOWER2` → `STATE_CYCLE_END`.
6. For each state, verify audibly that the correct relay channel clicks (only one relay should be energised at a time in this version of the firmware).
7. **Pass criterion:** each relay channel actuates in the correct state and de-actuates at the correct state transition.

### T-03 Continuity and Isolation Test
1. With the enclosure fully de-energised and locked out, perform a continuity test between:
   - Arduino 5 V and each mains phase conductor → must be open circuit
   - Arduino GND and each mains phase conductor → must be open circuit
   - Arduino GND and PE → must be open circuit (no shared ground)
   - Each contactor coil and the corresponding relay COM/NO → must be continuous when relay is energised
2. Perform a 500 V or 1000 V insulation resistance test between:
   - Each mains phase and PE → must be ≥ 1 MΩ (per local code)
   - Each mains phase and the enclosure chassis → must be ≥ 1 MΩ
3. **Pass criterion:** all continuity and insulation measurements meet the criteria above.

### T-04 Load Current Measurement
1. With the enclosure de-energised, connect a clamp meter around each load's phase conductor.
2. Energise the enclosure.
3. Trigger each load individually via the manual override.
4. Record the steady-state current and the inrush current (peak during first 100 ms).
5. **Pass criterion:** each load's steady-state current is within the contactor's rated current; each MCB does not trip on inrush.

### T-05 24-Hour Endurance Test
1. Configure the firmware with realistic cycle timings.
2. Energise the enclosure with all loads connected.
3. Run continuously for 24 hours.
4. Periodically record: enclosure internal temperature, relay module temperature, contactor temperatures, cycle count.
5. **Pass criterion:** no relay failure, no contactor failure, no thermal trip, no fuse blow, no firmware crash.

### T-06 Thermal Inspection
1. After 4 hours of continuous operation under load, perform an infrared thermal scan of:
   - Each contactor
   - Each MCB
   - The 5 V DC supply
   - The relay module
   - The enclosure interior
2. **Pass criterion:** no component exceeds its rated operating temperature; enclosure interior stays within the relay module's operating range (typically −10 °C to +50 °C).

### T-07 Manual Override Function Test
1. For each load, switch the manual override to MANUAL → load must energise regardless of Arduino state.
2. Switch the manual override to OFF → load must de-energise regardless of Arduino state.
3. Switch the manual override to AUTO → load must follow the Arduino's state machine.
4. **Pass criterion:** all three positions work correctly for all four loads.

### T-08 EPO Function Test
1. With the enclosure energised and a load running, press the EPO button.
2. **Pass criterion:** all loads de-energise immediately. The EPO must remain latched until manually reset.
3. After resetting the EPO, verify normal operation resumes.

## Recording Results

Each test result must be recorded in this file with:
- Tester name
- Test date
- Equipment used (model and serial)
- Environmental conditions (ambient temperature, humidity)
- Measured values
- Pass/fail verdict
- Anomalies or deviations

Any test that fails must be investigated and the root cause recorded before re-testing. Do not mark a test as passed on the basis of a re-test without documenting the original failure.
