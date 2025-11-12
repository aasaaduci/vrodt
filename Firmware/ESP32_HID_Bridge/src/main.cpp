#include <Arduino.h>
#include <NimBLEDevice.h>
#include "USB.h"
#include "USBHID.h"
#include "USBHIDGamepad.h"

USBHIDGamepad Gamepad;
static const char* SERVICE_UUID = "8b9a0001-6c38-4c94-9f5e-odt0shoe000001";
static const char* CHAR_UUID    = "8b9a0002-6c38-4c94-9f5e-odt0shoe000002";
struct Payload { float vx; float vy; uint8_t foot; uint8_t flags; } __attribute__((packed));
float s_vx=0, s_vy=0;

void setup() {
  USB.begin(); Gamepad.begin();
  NimBLEDevice::init("ODT-HID-BRIDGE");
  NimBLEScan* scan = NimBLEDevice::getScan();
  scan->setActiveScan(true);
  scan->start(5, false);
}

class CB: public NimBLEClientCallbacks{};
void subscribe(NimBLEAdvertisedDevice* d){
  NimBLEClient* c = NimBLEDevice::createClient();
  c->setClientCallbacks(new CB());
  if (!c->connect(d)) return;
  auto* svc = c->getService(SERVICE_UUID); if(!svc) return;
  auto* ch  = svc->getCharacteristic(CHAR_UUID); if(!ch) return;
  ch->subscribe(true, [](NimBLERemoteCharacteristic*, uint8_t* data, size_t len, bool){
    if (len==sizeof(Payload)){ Payload p; memcpy(&p,data,len); s_vx=p.vx; s_vy=p.vy; }
  });
}

void loop(){
  // Simple scan/connect loop (demo-grade)
  static bool connected=false;
  if(!connected){
    auto* scan = NimBLEDevice::getScan();
    NimBLEScanResults r = scan->start(3, false);
    for (int i=0;i<r.getCount();++i){
      auto* dev = r.getDevice(i);
      std::string name = dev->getName();
      if (name.find("ODT-SHOE")!=std::string::npos){ subscribe(dev); connected=true; break; }
    }
  }
  // Map velocity to stick axes
  auto toAxis = [](float v)->int16_t{
    v = max(-1.0f, min(1.0f, v));
    return (int16_t)(v*32767);
  };
  Gamepad.leftStick(toAxis(s_vy), toAxis(-s_vx));
  delay(10);
}