#ifndef __INC_LEDBOW_DISPLAYMODEISR_H
#define __INC_LEDBOW_DISPLAYMODEISR_H

#include <DisplayMode.h>

class DisplayModeIsr {
public:
  DisplayModeIsr();
  DisplayMode currentMode();
  void onInterrupt();

private:
  volatile bool interrupted;
  volatile unsigned long lastInterruptTime;
  DisplayMode mode;
};

#endif
