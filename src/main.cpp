#include <Arduino.h>
#include <Wire.h>

#include <TouchPad.h>

#define ISR_PIN 12
#define TRIGGER_PIN 14
#define TRIGGER_DURATION 100
#define TWOWIRE_SDA 5
#define TWOWIRE_SCL 4

IRAM_ATTR volatile int triggerCount = 0;

IRAM_ATTR void onTrigger_ISR() {
  triggerCount += 1;
}

TouchPad touchPad;

void setup() {
  Serial.begin(9600);
  Serial.println("\nSetup");

  pinMode(ISR_PIN, INPUT_PULLUP);
  pinMode(TRIGGER_PIN, OUTPUT);

  digitalWrite(TRIGGER_PIN, HIGH);
  attachInterrupt(ISR_PIN, onTrigger_ISR, FALLING);

  Wire.begin(TWOWIRE_SDA, TWOWIRE_SCL);
  touchPad.init();
  Serial.println("ChipId: " + String(touchPad.getChipId()));
}

void trigger() {
  digitalWrite(TRIGGER_PIN, LOW);
  delay(TRIGGER_DURATION);
  digitalWrite(TRIGGER_PIN, HIGH);
  delay(TRIGGER_DURATION);
}

void loop() {
  Serial.println("loop");
  delay(5000);

  auto x = ESP.getCycleCount();
  for (auto i = 0; i < 10; i += 1) {
    trigger();
  }
  auto y = ESP.getCycleCount() - x;
  Serial.println("trigger_ISR: " + String(triggerCount) + " (cycles: " + String(y) + ")");
}