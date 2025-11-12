# VRODT — Open DIY Omnidirectional VR Treadmill

An open, printable omnidirectional treadmill (ODT) designed for SteamVR locomotion and fabricated on a **Creality K2 Combo** (260×260×260 mm).

- ✅ Parametric OpenSCAD CAD for a 1.1 m concave bowl (tileable)
- ✅ ESP32-S3 firmware for IMU shoes (BNO085) + USB HID bridge
- ✅ OrcaSlicer profiles (Klipper flavor) for K2 Combo + CFS (multi-color)
- ✅ Open, automation-friendly stack (AGPL/GPL/MIT compatible)
- 🔜 Optional optical-flow shoe & Jetson Orin Nano vision tracker

> Starter pack ZIP with more docs and models is also available in Releases (or see `/Docs/ONBOARDING_AGENT.md`).

## Quick Start
1) Print tiles in PETG, assemble on 18 mm plywood base (see `/Docs/BUILD_STEPS.md`).
2) Flash `Firmware/ESP32_Shoe_IMU` to two ESP32-S3s, and `Firmware/ESP32_HID_Bridge` to one ESP32-S3.
3) Plug the HID Bridge to your PC; Steam will detect a gamepad. Map Left Stick to locomotion in Steam Input.
4) Use OrcaSlicer profiles under `/Profiles/OrcaSlicer` or import into your slicer.

## License
- Code: MIT (see `LICENSE`)
- CAD: CERN-OHL-P v2 (to keep hardware derivatives open)
- Profiles & docs: CC-BY 4.0

---