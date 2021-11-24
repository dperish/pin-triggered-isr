#include <Arduino.h>
#include <Wire.h>

#include <TouchPad.h>

#define ISR_PIN 12
#define TWOWIRE_SDA 5
#define TWOWIRE_SCL 4

IRAM_ATTR volatile int triggerCount = 0;
IRAM_ATTR void onTrigger_ISR()
{
  triggerCount += 1;
}

TouchPad touchPad;

void setup()
{
  Serial.begin(9600);

  Wire.begin(TWOWIRE_SDA, TWOWIRE_SCL);

  pinMode(ISR_PIN, INPUT_PULLUP);
  attachInterrupt(ISR_PIN, onTrigger_ISR, FALLING);

  touchPad.init();
  Serial.println("\n\nChipId: " + String(touchPad.getChipId()));
  Serial.println("Firmware Version: " + String(touchPad.getFirmwareVersion()));
  touchPad.setLowPowerMode(2);
}

void loop()
{
  if (triggerCount >= 1)
  {
    triggerCount = 0;

    auto detectionStatus = touchPad.getDetectionStatus();
    auto activeKey = touchPad.readActiveKey();

    if (detectionStatus > 0 && activeKey > 0)
    {
      Serial.printf("Key: %d \tStatus: %d\n", activeKey, detectionStatus);
    }
  }
}