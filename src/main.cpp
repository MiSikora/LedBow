#include <Arduino.h>
#include <DisplayModeIsr.h>

#define BUTTON_PIN 2

DisplayModeIsr modeIsr = DisplayModeIsr();

void onInterrupt() {
  modeIsr.onInterrupt();
}

void setup() {
  Serial.begin(57600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onInterrupt, RISING);
}

void loop() {
  unsigned long sleepTime = 1000;
  Serial.println(modeIsr.currentMode());
  delay(sleepTime);
}
