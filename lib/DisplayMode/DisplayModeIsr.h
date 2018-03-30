#ifndef __INC_LEDBOW_DISPLAYMODEISR_H
#define __INC_LEDBOW_DISPLAYMODEISR_H

class DisplayModeIsr {
public:
  DisplayModeIsr() {
    interrupted = false;
    lastInterruptTime = 0;
    mode = 0;
  }

  void onInterrupt(unsigned long interruptTime) {
    if (interruptTime - lastInterruptTime > 200) {
      lastInterruptTime = interruptTime;
      interrupted = true;
    }
  }

  int currentMode(int modeCount) {
    if (interrupted) {
      interrupted = false;
      mode = (mode + 1) % modeCount;
    }
    return mode;
  }


private:
  volatile bool interrupted;
  volatile unsigned long lastInterruptTime;
  int mode;
};

#endif
