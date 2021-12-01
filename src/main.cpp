#include <Arduino.h>
#include <Wire.h>

#include <TouchPad.h>

#define TWOWIRE_SDA 5
#define TWOWIRE_SCL 4
#define ISR_PIN 12

TouchPad touchPad;

void checkForKeyPresses()
{
  if (!touchPad.isKeyActive) {
    return;
  }
  
  touchPad.isKeyActive = false;

  int activeKey = touchPad.readActiveKey();

  if (activeKey > 0)
  {
    Serial.printf("active key: %d\n", activeKey);
  }
}

void setup()
{
  Serial.begin(921600);
  delay(10);

  touchPad.init(TWOWIRE_SDA, TWOWIRE_SCL, ISR_PIN);
  touchPad.setLowPowerMode(1);

  Serial.println("\nChipId: " + String(touchPad.getChipId()));
  Serial.println("Firmware Version: " + String(touchPad.getFirmwareVersion()));
}

void loop()
{
  checkForKeyPresses();
}