# Project Overview — STP Four-Relay Control System

## Summary

This project provides a four-relay controller documentation and firmware starting point for a Sewage Treatment Plant (STP) process tank. The controller drives four independent loads through a 4-channel relay module controlled by an Arduino Uno. The four loads, preserved from the original concept, are:

1. **Blower 1** — primary aeration blower
2. **MBBR** — Moving Bed Biofilm Reactor aeration/mixing unit
3. **Sludge system** — sludge recirculation / wasting
4. **Blower 2** — secondary aeration blower

## Status

This is a PROPOSED design package. The hardware has not been verified against any inspected original sketch. The firmware is a IMPLEMENTED starting point that compiles on an Arduino Uno. No physical test has been performed on this package, so all test items are NOT YET TESTED.

## Scope

The package covers the control concept, hardware proposal, firmware starting point, wiring and isolation documentation, test plan, safety considerations, and limitations. It does not cover biological process design, dissolved oxygen feedback control, SCADA integration, or regulatory compliance for a real STP. These items are out of scope for this portfolio entry but are listed in `development-roadmap.md` as future improvements.

## Audience

The package is intended for the original designer (to confirm or correct pin assignments and timing values), for portfolio review by instructors or prospective employers, and for any engineer continuing development of the controller. It is not intended for direct deployment in a live STP without engineering review.
