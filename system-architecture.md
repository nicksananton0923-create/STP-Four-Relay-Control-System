# System Architecture — STP Four-Relay Control System

## Layered Architecture

The system uses a layered isolation architecture that is standard practice for low-voltage control of mains-powered motor loads. Each layer provides a distinct function and a distinct isolation boundary.

```
┌─────────────────────────────────────────────────────────────────────┐
│  Layer 1 — Control Logic (Arduino Uno, 5 V)                          │
│  • State machine for the 4-load cycle                                │
│  • Configurable timing parameters                                    │
│  • Serial Monitor diagnostics                                       │
└───────────────────────────┬─────────────────────────────────────────┘
                            │ 4× digital GPIO (5 V logic)
                            ▼
┌─────────────────────────────────────────────────────────────────────┐
│  Layer 2 — Relay Module (optocoupler isolation)                       │
│  • 4-channel active-low relay module                                │
│  • Optocoupler between Arduino side and relay coil side              │
│  • Common ground on Arduino side only                                │
└───────────────────────────┬─────────────────────────────────────────┘
                            │ 4× dry contact (volt-free)
                            ▼
┌─────────────────────────────────────────────────────────────────────┐
│  Layer 3 — Contactor Stage (mains-side switching)                     │
│  • 4× independent contactors, one per load                          │
│  • Each contactor coil driven by one relay channel                   │
│  • Flyback diodes / RC snubbers on each coil                         │
└───────────────────────────┬─────────────────────────────────────────┘
                            │ 4× mains circuit (fused, RCD-protected)
                            ▼
┌─────────────────────────────────────────────────────────────────────┐
│  Layer 4 — Loads                                                     │
│  • Blower 1, MBBR, Sludge system, Blower 2                          │
└─────────────────────────────────────────────────────────────────────┘
```

## Power Distribution

Two galvanically-isolated power domains are used:

- **Low-voltage domain:** 5 V DC regulated supply feeding the Arduino Uno and the input side of the relay module. Sourced from a small mains-derived SMPS in the enclosure.
- **Mains domain:** 230 V AC (or local voltage) feeding the contactor outputs to the loads. Each load circuit has its own fuse and the entire enclosure is RCD-protected.

The two domains share no common conductor except the protective earth (PE), which is bonded to the enclosure chassis.

## Firmware Architecture

The firmware implements a single-file state machine:

1. **State definitions:** `STATE_IDLE`, `STATE_BLOWER1`, `STATE_MBBR`, `STATE_SLUDGE`, `STATE_BLOWER2`, `STATE_CYCLE_END`.
2. **Timing:** each state has an `_ON_MS` parameter; transitions occur when the elapsed time exceeds the parameter.
3. **Output mapping:** each state drives a specific combination of the four relay outputs.
4. **Diagnostics:** Serial Monitor prints state, elapsed time, and next state at every transition.

The firmware is intentionally simple to support education and further development. It does not include RTOS, interrupts, or sensor feedback — these are listed as future improvements.
