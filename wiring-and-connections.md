# Wiring and Connections — STP Four-Relay Control System

## Pin Assignments

**STATUS: NOT VERIFIED.** The pin assignments below are placeholders. They have not been confirmed against any inspected original sketch. Before wiring, confirm each assignment against the original design and update the firmware `#define` block accordingly.

| Function | Arduino Uno Pin | Status | Notes |
|---|---|---|---|
| Relay channel 1 (Blower 1) | D2 | PROPOSED — NOT VERIFIED | Default placeholder |
| Relay channel 2 (MBBR) | D3 | PROPOSED — NOT VERIFIED | Default placeholder |
| Relay channel 3 (Sludge) | D4 | PROPOSED — NOT VERIFIED | Default placeholder |
| Relay channel 4 (Blower 2) | D5 | PROPOSED — NOT VERIFIED | Default placeholder |
| Serial Monitor TX | D0 (hardware) | IMPLEMENTED | 9600 baud |
| Serial Monitor RX | D1 (hardware) | IMPLEMENTED | 9600 baud |
| (future) Pause button | D6 | PROPOSED | Not implemented in v1 |
| (future) Reset button | D7 | PROPOSED | Not implemented in v1 |
| (future) Status LED | D13 | PROPOSED | Onboard LED, not yet used |

## Relay Module Wiring

The 4-channel relay module is assumed to be optocoupler-isolated and active-low. This is a common configuration for low-cost relay modules. The wiring is:

```
Arduino 5V  ──────────►  Relay module VCC
Arduino GND ──────────►  Relay module GND (input side)
Arduino D2  ──────────►  Relay module IN1
Arduino D3  ──────────►  Relay module IN2
Arduino D4  ──────────►  Relay module IN3
Arduino D5  ──────────►  Relay module IN4
```

If the relay module has a separate JD-VCC jumper (used to isolate the relay coil supply from the Arduino supply), remove the jumper and feed the JD-VCC pin from a separate 5 V supply with its own ground. This provides true galvanic isolation. This configuration is RECOMMENDED but not verified for this project.

## Contactor Wiring (per load)

Each of the four loads is switched by its own contactor. The contactor coil is driven by the corresponding relay channel's dry contact. For a 24 V DC coil contactor:

```
24V DC + ─────► Flyback diode cathode ─────► Contactor coil + 
                                                      │
24V DC − ─────► Flyback diode anode      Contactor coil −
                                                      │
Relay COM ────► ───────────────────────────────────────┘
Relay NO  ────► (returns to 24V DC − through the coil)
```

For a 230 V AC coil contactor, replace the flyback diode with an RC snubber (0.1 µF X2 capacitor in series with 100 Ω resistor) across the coil.

## Mains Wiring

The mains side of each contactor is wired as follows:

```
RCD output L ──► MCB (per load) ──► Contactor NO terminal ──► Load L
RCD output N ─────────────────────────────────────────────► Load N
PE bus ──────────────────────────────────────────────────► Load PE
```

Each load circuit is independently fused and is energised only when its contactor is closed. The RCD protects the entire enclosure.

## Segregation Requirements

Low-voltage wiring (Arduino, relay module inputs, 24 V DC contactor coils if used) and mains wiring must be physically segregated inside the enclosure. The recommended practice is:

- Use separate cable ducts for LV and mains.
- Maintain at least 25 mm physical separation between LV and mains conductors where they must cross.
- Use colour-coded wiring: blue for 24 V DC, brown/black/grey for mains phases, green/yellow for protective earth.
- Label every conductor at both ends with a unique identifier that matches the wiring schedule.

## Earth Bonding

The enclosure chassis must be bonded to the protective earth (PE) bus. The PE bus must be connected to the building's main earthing terminal with a conductor of appropriate cross-section. All exposed conductive parts of the loads (motor frames, etc.) must also be bonded to PE.
