# Components and Bill of Materials — STP Four-Relay Control System

## Bill of Materials

All items in this BOM are PROPOSED. No item has been confirmed against an inspected original parts list. Quantities and ratings are typical starting values and must be verified by the original designer or a qualified electrical engineer before procurement.

| Ref | Component | Quantity | Rating / Part | Status | Notes |
|---|---|---|---|---|---|
| U1 | Arduino Uno R3 | 1 | ATmega328P, 5 V logic | PROPOSED | Main controller |
| U2 | 4-channel relay module (optocoupler-isolated) | 1 | 5 V coil, 10 A contact (typical) | PROPOSED | Active-low trigger assumed; verify |
| K1–K4 | Contactors | 4 | Coil voltage per local mains; contact rating per load | PROPOSED | One per load |
| D1–D4 | Flyback diodes (for DC coils) or RC snubbers (for AC coils) | 4 | 1N4007 (DC) or 0.1 µF + 100 Ω (AC) | PROPOSED | Across each contactor coil |
| F1–F4 | MCB / fuse per load | 4 | Rating per load current | PROPOSED | One per load circuit |
| F0 | RCD / GFCI upstream of enclosure | 1 | 30 mA trip, rated for total load | PROPOSED | Mandatory earth leakage protection |
| PS1 | 5 V DC regulated supply (SMPS) | 1 | ≥ 1 A output | PROPOSES | Arduino + relay module power |
| SW1–SW4 | Manual override selector switches (AUTO / MANUAL / OFF) | 4 | 3-position rotary, suitable for cabinet mounting | PROPOSED | Per-load manual control |
| SW0 | EPO button (mushroom-head, latching) | 1 | NC contact, rated for mains coil current | PROPOSED | Mandatory safety cut-off |
| ENC1 | DIN-rail enclosure | 1 | IP54 minimum, with ventilation | PROPOSED | STP plant environment |
| — | DIN rails, terminals, cable ducts, glands, labels | — | — | PROPOSED | Standard cabinet hardware |

## Notes on Component Selection

The contactor coil voltage is one of the most important selections in this BOM. Two common options are:

- **24 V DC coil:** allows the relay module to drive the contactor directly (via the dry contact), with a small 24 V DC supply in the enclosure. Safer for maintenance.
- **230 V AC coil:** the relay module's dry contact switches mains directly to the contactor coil. Simpler wiring but exposes mains on the relay side of the cabinet, which must be carefully segregated.

The selection depends on the contactor series available locally and on the installer's preference. Either option is acceptable provided the wiring, fusing, and labelling match.

## What This BOM Does Not Include

This BOM does not include:

- The loads themselves (blowers, MBBR motor, sludge pump) — these are plant-specific
- The mains distribution board upstream of the enclosure
- The STP process tank instrumentation (DO sensor, level sensor, flow meter)
- Any communication or SCADA hardware
- Backup power or UPS

These items are out of scope for the controller package and would be specified separately by the plant designer.
