#ifndef __INC_LEDBOW_DISPLAYMODEISR_H
#define __INC_LEDBOW_DISPLAYMODEISR_H

#include <DisplayMode.h>

class DisplayModeIsr {
public:
  DisplayModeIsr() {
    interrupted = false;
    mode = NONE;
    lastInterruptTime = 0;
  }
  DisplayMode currentMode();
  void onInterrupt();

private:
  volatile bool interrupted;
  volatile unsigned long lastInterruptTime;
  DisplayMode mode;
};

#endif
