# Safety Considerations — STP Four-Relay Control System

## Mains Voltage Safety

This project involves switching mains voltage to inductive motor loads. Mains voltage can cause fatal electric shock. All work on the mains side of the enclosure must be performed by a person competent to work with mains voltage and in compliance with local electrical codes (e.g. BS 7671 in the UK, NEC in the US, SLS in Sri Lanka, IEC 60364 internationally).

Before any work on the enclosure:

1. Isolate the upstream supply using the lockable isolator.
2. Apply a personal lock and tag (lockout-tagout, LOTO).
3. Verify dead with a calibrated voltage tester.
4. Confirm the RCD will not energise the enclosure (test the RCD's trip button with the enclosure isolated).

## Isolation

The architecture provides two layers of isolation between the Arduino and the mains loads:

1. **Optocoupler isolation** on the relay module — protects the Arduino from the relay coil circuit.
2. **Contactor isolation** — the contactor's dry contact is the only connection between the relay module and the mains load. The relay module never carries mains voltage directly.

This double-isolation pattern is standard industrial practice and must be preserved in any modification to the design. Removing either layer creates a serious safety hazard.

## Overcurrent Protection

Each mains load circuit must be independently fused or protected by its own MCB rated for the load's full-load current and inrush characteristics. A single upstream fuse for the entire enclosure is not acceptable because a fault on one load would de-energise the entire controller.

## Earth Leakage Protection

A residual current device (RCD) with a 30 mA trip rating must protect the enclosure. The RCD protects against earth faults that could otherwise cause electric shock. The RCD must be tested regularly using its built-in test button.

## Inductive Load Protection

Each contactor coil (and each load motor) is an inductive load that produces back-EMF when its current is interrupted. Without suppression, this back-EMF can damage the relay contacts, the contactor, and adjacent electronics. The following suppression is required:

- **DC contactor coils:** fit a flyback diode (e.g. 1N4007) across the coil, cathode to positive.
- **AC contactor coils:** fit an RC snubber (0.1 µF X2 capacitor in series with 100 Ω resistor) across the coil.
- **Load motors:** the motor's own terminal box should already include suppression; if not, fit an additional RC snubber across the motor terminals.

## Lockout-Tagout (LOTO)

A lockable upstream isolator must be fitted so that maintenance can be performed safely. The LOTO procedure must follow the site's standard lockout-tagout policy. Multiple locks (hasps) may be required if more than one person is working on the enclosure.

## Emergency Power Off (EPO)

An EPO button must cut all mains power to the enclosure independently of the Arduino. The EPO must:

- Be a latching type (must remain actuated until manually reset).
- Be a mushroom-head type, red, with a yellow background.
- Be mounted in a prominent, accessible location.
- Break the upstream mains feed, not just the control circuit.
- Be tested regularly.

## Enclosure Rating

The enclosure must be rated for the STP plant environment. Typical STP plant conditions include:

- High humidity (often > 90 %)
- Hydrogen sulphide and other corrosive gases
- Occasional water spray during tank cleaning
- Wide temperature range

An IP54 enclosure is the minimum acceptable rating. IP65 or IP66 is preferred for direct plant installation. Ventilation must be provided to prevent condensation; this may require a breather drain and a small fan with appropriate IP rating.

## Operator Safety

The enclosure door must be interlocked with the upstream isolator such that opening the door automatically isolates the mains, OR the door must be lockable with a key available only to authorised personnel. Warning labels must be affixed to the enclosure: "DANGER — mains voltage inside", "AUTHORISED PERSONNEL ONLY", "LOCKOUT BEFORE SERVICING".

## Firmware Safety

The firmware enters a known safe state on power-on (`STATE_IDLE`, all relays OFF). This is a deliberate design choice: if the Arduino resets during operation, all loads are de-energised rather than left in their previous state. A future improvement is to add a watchdog timer that resets the Arduino if the firmware crashes.

## Out of Scope

This safety document does not cover:
- Biological hazards of the STP process (these are covered by the plant's safety documentation)
- Mechanical hazards of the loads themselves
- Confined space entry procedures for the STP tank
- Hydrogen sulphide gas monitoring
- Sludge handling safety

These items are the responsibility of the plant operator and are out of scope for the controller package.
