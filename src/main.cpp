#include <Arduino.h>
#include <DisplayMode.h>

DisplayMode mode = NONE;

void setup() {
  Serial.begin(57600);
}

void loop() {
  unsigned long sleepTime = 1000;
  Serial.println(mode);
  mode++;
  delay(sleepTime);
}
