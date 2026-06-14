# Motor and Power Notes

This document covers the motor choice, estimated current draw, payload assumptions, and power planning notes for the pan/tilt platform.

## Motor Selection

This design uses common 28BYJ-48 5 V geared stepper motors.

These motors are inexpensive and widely available, making them useful for lightweight positioning fixtures and proof-of-concept builds. They should not be treated as high-torque actuators.

## Typical 28BYJ-48 Specifications

Typical published 28BYJ-48 specifications include:

| Parameter | Typical Value |
|---|---|
| Rated voltage | 5 V DC |
| Motor type | 4-phase unipolar geared stepper |
| Step / stride angle | 5.625° / 64 |
| Approximate theoretical output resolution | ~0.088° per step |
| Published pull-in torque | ~300 gf·cm |

The theoretical step resolution is not the same as real platform accuracy.

Actual pointing accuracy will be affected by:

- gear backlash
- 3D-printed part tolerances
- bearing fit
- flex
- load balance
- motor quality
- driver behavior
- calibration
- how the load is mounted

## Torque and Payload Limit

No formal payload rating has been established.

Until tested, this platform should be treated as suitable for lightweight test articles only, such as:

- small antennas
- compact sensors
- small reflectors
- lightweight camera modules
- test coupons or RF samples

Payload capacity depends on:

- the weight of the mounted object
- the center of mass of the mounted object
- the distance between the load and the tilt axis
- tilt angle
- print material
- bearing fit
- motor quality
- power supply performance

A small balanced load close to the tilt axis will perform much better than a heavier off-center load.

## Estimated Current Draw

Approximate planning values:

| Component | Estimated Current |
|---|---|
| Wemos D1 Mini / ESP8266 | plan for 250-500 mA available at 5 V input |
| One 28BYJ-48 motor + ULN2003 driver | ~250-300 mA while energized |
| Two 28BYJ-48 motors + drivers | ~500-600 mA while energized |

A 5 V supply rated for at least 1.5 A is recommended.

A 5 V / 2 A supply gives more practical margin.

## Holding Current

Stepper motors may continue drawing current while holding position, even when they are not visibly moving.

This means the platform can draw significant current while stationary.

Do not rely on a weak USB port or marginal regulator for final testing.

## Power Supply Guidance

For most real builds:

- use a dedicated 5 V supply for the stepper motors
- make sure the supply can handle motor current while both axes are energized
- connect grounds between motor power and ESP8266 logic
- keep wiring short and secure
- account for motor stall or holding current
- add bulk capacitance near the motor supply if needed
- avoid powering motors from the Wemos D1 Mini regulator

## Logic and Motor Power

The ESP8266 should be powered in a way that avoids brownouts during Wi-Fi activity or motor movement.

Possible approaches:

- power the Wemos D1 Mini from a reliable 5 V supply through its 5 V input
- use a separate 5 V supply rail for motors
- share common ground between logic and motor supply
- avoid routing motor current through the controller board

## Driver Notes

The common 28BYJ-48 motor is often paired with a ULN2003 driver board.

That combination is cheap and simple, but not especially efficient.

Possible future upgrades:

- different geared stepper motors
- bipolar stepper conversion
- better stepper drivers
- servos with feedback
- closed-loop position sensing
- higher-torque motors for heavier test articles

## Accuracy Notes

Do not treat the calculated step size as final pointing accuracy.

The platform may move in small increments, but real accuracy depends on the entire mechanical system.

Potential sources of error:

- gear train backlash
- motor skipped steps
- flex in printed parts
- bearing clearance
- tilt-frame play
- mounting surface flex
- unbalanced loads
- software rounding
- homing repeatability

## Recommended Testing

Before mounting any valuable test article:

1. test each motor unloaded
2. verify direction of travel
3. verify limit switch behavior
4. test slow movement commands
5. test full travel range
6. test holding behavior
7. test with a lightweight dummy load
8. monitor motor and driver temperature
9. verify repeatability
10. increase load only after basic motion is reliable
