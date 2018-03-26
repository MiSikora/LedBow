#ifndef __INC_LEDBOW_DISPLAYMODEISR_H
#define __INC_LEDBOW_DISPLAYMODEISR_H

#include <DisplayMode.h>

class DisplayModeIsr {
public:
  DisplayModeIsr() {
    interrupted = false;
    lastInterruptTime = 0;
    mode = NONE;
  }

  void onInterrupt(unsigned long interruptTime) {
    if (interruptTime - lastInterruptTime > 200) {
      lastInterruptTime = interruptTime;
      interrupted = true;
    }
  }

  DisplayMode currentMode() {
    if (interrupted) {
      interrupted = false;
      mode++;
    }
    return mode;
  }


private:
  volatile bool interrupted;
  volatile unsigned long lastInterruptTime;
  DisplayMode mode;
};

#endif
