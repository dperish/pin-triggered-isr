#include <Arduino.h>
#include <Wire.h>

#include <TouchPad.h>

#define TWOWIRE_SDA 5
#define TWOWIRE_SCL 4
#define ISR_PIN 12

TouchPad touchPad;

void onKeyPress(int keyAddress) {
  Serial.println("Key: " + String(keyAddress));
}

void setup()
{
  Serial.begin(9600);

  touchPad.init(
    TWOWIRE_SDA, 
    TWOWIRE_SCL, 
    ISR_PIN, 
    onKeyPress
  );

  touchPad.setLowPowerMode(2);

  Serial.println("\n\nChipId: " + String(touchPad.getChipId()));
  Serial.println("Firmware Version: " + String(touchPad.getFirmwareVersion()));


}

void loop()
{
}