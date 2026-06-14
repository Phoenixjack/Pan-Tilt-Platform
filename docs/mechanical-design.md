# Mechanical Design

This document covers the mechanical design notes for the pan/tilt platform.

The design is intended as a lightweight positioning fixture for RF, antenna, sensor, camera, or general directional testing. It is not a commercial motion-control product or a finished load-rated tripod head.

## CAD Files

The 3D model and mechanical files are hosted on GrabCAD:

[Pan-Tilt Platform on GrabCAD](https://grabcad.com/library/pan-tilt-platform-2)

Because GrabCAD account restrictions may limit direct project cross-linking, the matching firmware repository can be found on GitHub under:

```text
Phoenixjack / Pan-Tilt-Platform
```

## Mechanical Goals

The design was intended to provide:

- low-cost pan and tilt motion
- tripod mounting
- flexible test article attachment
- space for embedded electronics
- mechanical travel limits
- printable or prototype-friendly parts
- enough stiffness for lightweight test articles

## Major Mechanical Features

### Base Housing

The base houses the lower pan-stage components, motor mounts, electronics, limit switch features, and tripod interface.

![Base internals](../images/PanTiltPlatform-BaseInternals-Isometric.png)

### Rotating Pan Stage

The pan stage rotates around the central axis and provides the lower motion stage for the tilt frame.

The design includes provisions for stepper motor drive and rotational support.

### Tilt Frame

The upper tilt frame holds the test mounting surface and allows angular adjustment of the mounted object.

![Full assembly](../images/PanTiltPlatform-Overall-Isometric.png)

### Honeycomb Mounting Surface

The honeycomb-style surface provides a flexible way to secure test articles.

Potential uses include:

- small antennas
- sensor boards
- reflectors
- RF samples
- lightweight camera modules
- test coupons

The honeycomb pattern is intended to provide multiple tie-down or attachment points without requiring a custom plate for every test item.

### Tripod Interface

The platform was originally designed around the Oberwerk TR3 tripod, but the tripod interface is based on a common 1/4-20 threaded mount.

![Tripod interface](../images/PanTiltPlatform-Base-Isometric.png)

The design uses:

- McMaster-Carr 91813A170 1/4-20 nut
- 3D printed jam nut or retainer
- internal nut capture for stronger threaded engagement

This allows the printed body to interface with a metal threaded insert rather than relying entirely on printed plastic threads.

## Hardware Notes

The design references the following hardware:

| Item | Purpose |
|---|---|
| 28BYJ-48 geared stepper motors | Pan and tilt motion |
| ULN2003-style driver boards | Stepper motor drive |
| Wemos D1 Mini / ESP8266 | Embedded controller |
| McMaster-Carr 7658K16 subminiature snap-action switches | Travel limit detection |
| McMaster-Carr 96455K132 ball bearings | Horizontal support / stability |
| McMaster-Carr 91813A170 1/4-20 nut | Tripod mount threading |

Verify dimensions and availability before building. Part numbers are included as design references, not guaranteed procurement instructions.

## Bearings and Stability

The design includes provisions for ball bearings to improve horizontal stability.

Bearing fit, print tolerance, material choice, and assembly quality will affect final stiffness and smoothness.

## Limit Switches

Mechanical limit switches are included to prevent excessive rotation or travel.

Limit switches should be treated as a safety and homing aid, not as the only protection against mechanical overtravel. Software limits should also be implemented.

## Print / Fabrication Notes

No final print settings have been validated.

Likely considerations:

- use a material stiff enough for the expected payload
- avoid weak layer orientation around motor mounts and tripod interface
- verify bearing pocket fit
- verify nut capture fit
- inspect moving clearances before applying motor power
- test travel slowly before full operation

## Payload Notes

No formal payload rating has been established.

The design should be treated as suitable for lightweight test articles only until load testing is performed.

Practical payload capacity depends on:

- object weight
- center of mass
- tilt angle
- motor quality
- print material
- bearing fit
- gear backlash
- platform balance
- mounting method

## Known Mechanical Limitations

- prototype design
- no formal load rating
- no validated print settings
- motor torque is limited
- backlash from geared steppers may affect accuracy
- 3D-printed part flex may affect repeatability
- final assembly tolerances are builder-dependent

## Future Mechanical Improvements

Possible improvements:

- add dimensioned drawings
- add exploded assembly view
- add hardware BOM
- add print orientation guidance
- add bearing fit notes
- add switch adjustment notes
- add payload test results
- add calibration procedure
- add photos of a physical build
