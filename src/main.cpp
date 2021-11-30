#include <Arduino.h>
#include <Wire.h>

#include <TouchPad.h>

#define TWOWIRE_SDA 5
#define TWOWIRE_SCL 4
#define ISR_PIN 12

TouchPad touchPad;

volatile bool keyPresses = false;
IRAM_ATTR static void onKeyDown_ISR() {
  Serial.print("onKeyDown_ISR\n");
  keyPresses = true;
}

void setup()
{
  Serial.begin(9600);

  Wire.begin(TWOWIRE_SDA, TWOWIRE_SCL);
  delay(1000);

  pinMode(ISR_PIN, INPUT_PULLUP);
  attachInterrupt(ISR_PIN, onKeyDown_ISR, FALLING);

  touchPad.init();
  touchPad.setLowPowerMode(2);

  Serial.println("\n\nChipId: " + String(touchPad.getChipId()));
  Serial.println("Firmware Version: " + String(touchPad.getFirmwareVersion()));

}

void loop()
{



  if (keyPresses) {
    keyPresses = false;
    
    int activeKey = touchPad.readActiveKey();

    if (activeKey > 0) {
      Serial.printf("active key: %d\n", activeKey);
    }
  }

}