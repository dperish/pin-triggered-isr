#include <Arduino.h>
#include <Wire.h>

#include <TouchPad.h>

#define ISR_PIN 12
#define TWOWIRE_SDA 5
#define TWOWIRE_SCL 4

IRAM_ATTR void onKeyDown_ISR(void* touchPad)
{
    auto touchPadRef = static_cast<TouchPad*>(touchPad);

    auto detectionStatus = touchPadRef->getDetectionStatus();
    auto activeKey = touchPadRef->readActiveKey();

    if (detectionStatus > 0 && activeKey > 0)
    {
      Serial.printf("onKeyDown_ISR - Key: %d \tStatus: %d\n", activeKey, detectionStatus);
    }
}

TouchPad touchPad;

void setup()
{
  Serial.begin(9600);

  Wire.begin(TWOWIRE_SDA, TWOWIRE_SCL);

  pinMode(ISR_PIN, INPUT_PULLUP);
  attachInterruptArg(ISR_PIN, onKeyDown_ISR, &touchPad, FALLING);

  touchPad.init();
  Serial.println("\n\nChipId: " + String(touchPad.getChipId()));
  Serial.println("Firmware Version: " + String(touchPad.getFirmwareVersion()));
  touchPad.setLowPowerMode(2);
}

void loop()
{
}