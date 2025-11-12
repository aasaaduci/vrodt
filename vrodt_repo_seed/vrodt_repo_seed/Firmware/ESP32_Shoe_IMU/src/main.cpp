#include <Arduino.h>
#include <Adafruit_BNO08x.h>
#include <NimBLEDevice.h>

Adafruit_BNO08x bno08x;
NimBLEServer* pServer = nullptr;
NimBLECharacteristic* pChar = nullptr;

static const char* SERVICE_UUID = "8b9a0001-6c38-4c94-9f5e-odt0shoe000001";
static const char* CHAR_UUID    = "8b9a0002-6c38-4c94-9f5e-odt0shoe000002";

struct Payload { float vx; float vy; uint8_t foot; uint8_t flags; } __attribute__((packed));

void setup() {
  Serial.begin(115200);
  if(!bno08x.begin()){ while(1) delay(10); }
  bno08x.enableReport(SH2_LINEAR_ACCELERATION);

  NimBLEDevice::init("ODT-SHOE");
  pServer = NimBLEDevice::createServer();
  auto* svc = pServer->createService(SERVICE_UUID);
  pChar = svc->createCharacteristic(CHAR_UUID, NIMBLE_PROPERTY::NOTIFY);
  svc->start();
  NimBLEAdvertising* adv = NimBLEDevice::getAdvertising();
  adv->addServiceUUID(SERVICE_UUID);
  adv->start();
}

void loop() {
  sh2_SensorValue_t e;
  float vx=0, vy=0;
  while (bno08x.getSensorEvent(&e)) {
    if (e.sensorId == SH2_LINEAR_ACCELERATION) {
      vx = e.un.linearAcceleration.x * 0.02f;
      vy = e.un.linearAcceleration.y * 0.02f;
    }
  }
  static uint32_t t0=0; if (millis()-t0>20){ t0=millis();
    Payload p{vx,vy,0,0};
    pChar->setValue((uint8_t*)&p, sizeof(p));
    pChar->notify(true);
  }
  delay(1);
}