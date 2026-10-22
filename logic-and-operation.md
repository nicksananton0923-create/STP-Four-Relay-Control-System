# Logic and Operation — STP Four-Relay Control System

## State Machine

The proposed control cycle moves through five operational states plus an idle state. The exact duration of each state is configurable in the firmware source file. The state names, durations, and outputs are listed below.

| State | Output pattern (B1, M, S, B2) | Default duration | Notes |
|---|---|---|---|
| `STATE_IDLE` | OFF, OFF, OFF, OFF | 5 s | Power-on safe state |
| `STATE_BLOWER1` | ON, OFF, OFF, OFF | configurable | Primary aeration |
| `STATE_MBBR` | OFF, ON, OFF, OFF | configurable | MBBR mixing/aeration |
| `STATE_SLUDGE` | OFF, OFF, ON, OFF | configurable | Sludge recirculation/wasting |
| `STATE_BLOWER2` | OFF, OFF, OFF, ON | configurable | Secondary aeration |
| `STATE_CYCLE_END` | OFF, OFF, OFF, OFF | 10 s | Settling / inter-cycle gap |

The cycle repeats indefinitely after `STATE_CYCLE_END`. The order is preserved from the user's original concept: Blower 1 → MBBR → Sludge → Blower 2. This order can be changed by editing the state table in the firmware.

## Output Mapping

Each state maps to a specific bit pattern on the four relay outputs. The firmware uses `#define` constants so that the mapping is easy to read and modify:

```cpp
// Output pattern per state (1 = relay ON, 0 = relay OFF)
// Format: {BLOWER1, MBBR, SLUDGE, BLOWER2}
```

Because the relay module is assumed to be active-low (a common configuration for optocoupler-isolated relay modules), the firmware inverts the logical output before writing to the GPIO pins. This assumption is PROPOSED and must be confirmed against the actual relay module's datasheet. If the module is active-high, the inversion must be removed.

## Power-On Behaviour

On power-on, the firmware enters `STATE_IDLE` for 5 seconds with all relays OFF. This provides a visible "controller ready" indication on the Serial Monitor and gives the operator a chance to confirm that the controller has booted correctly before any load is energised. After the idle period, the cycle begins at `STATE_BLOWER1`.

## Manual Override

The proposed design includes a hardware manual-override facility in the form of physical selector switches wired in parallel with each contactor's relay. In AUTO mode, the contactor is controlled by the relay. In MANUAL mode, the contactor is forced ON regardless of the Arduino state. In OFF mode, the contactor is forced OFF regardless of the Arduino state. This is a standard industrial pattern that allows maintenance without depending on the Arduino's continued operation.

The manual override switches are NOT VERIFIED in the original design and must be confirmed before implementation.

## Cycle Pause and Reset

The firmware exposes a Serial Monitor command to pause the cycle (all relays OFF, state machine halted) and to reset the cycle to `STATE_IDLE`. This supports testing and commissioning. No hardware pause/reset button is implemented in this version; it is listed as a future improvement.
