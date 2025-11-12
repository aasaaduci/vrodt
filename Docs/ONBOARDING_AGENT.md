# 🧠 Project ODT-K2: DIY Omnidirectional VR Treadmill + Open Slicer Stack

**Owner:** Ali Saad  
**Agent:** Codex Engineering Assistant  
**Repo:** `aasaaduci/vrodt`

## Mission
Deliver a printable omnidirectional treadmill with IMU shoes and an open slicer stack (OrcaSlicer/Cura) for Creality K2 Combo. All outputs must be open-licensed.

## Deliverables
- CAD (OpenSCAD): bowl tiles, ribs, ring, clamps, shoe soles
- Firmware: ESP32-S3 Shoe IMU + ESP32-S3 USB HID Bridge
- Slicer: OrcaSlicer profiles for K2 Combo + CFS (Klipper flavor)
- Docs: build steps, wiring, safety, EULA risk register
- CI: PlatformIO firmware build

## Task Board (MVP)
- [ ] Validate tile tolerances, export STLs
- [ ] Flash firmware and verify BLE notifications
- [ ] SteamVR mapping test (latency < 20 ms)
- [ ] Generate Orca profiles & start/end macros
- [ ] Optional: add PMW3360 optical-flow module

See `/Docs/BUILD_STEPS.md` and `/Docs/WIRING.md`.