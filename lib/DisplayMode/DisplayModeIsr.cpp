#include <DisplayModeIsr.h>
#include <Arduino.h>

DisplayMode DisplayModeIsr::currentMode() {
  if (interrupted) {
    interrupted = false;
    mode++;
  }
  return mode;
}

void DisplayModeIsr::onInterrupt() {
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > 200) {
    interrupted = true;
  }
  lastInterruptTime = interruptTime;
}
