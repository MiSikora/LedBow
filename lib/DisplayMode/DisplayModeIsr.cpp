#include <DisplayModeIsr.h>

DisplayModeIsr::DisplayModeIsr() {
  interrupted = false;
  mode = NONE;
}

DisplayMode DisplayModeIsr::currentMode() {
  if (interrupted) {
    interrupted = false;
    mode++;
  }
  return mode;
}

void DisplayModeIsr::onInterrupt() {
  interrupted = true;
}
