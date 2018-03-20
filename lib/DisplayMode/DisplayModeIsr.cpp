#include <DisplayModeIsr.h>
#include <Arduino.h>

DisplayModeIsr::DisplayModeIsr() {
  interrupted = false;
  mode = NONE;
  lastInterruptTime = 0;
}

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
