#ifndef __INC_LEDBOW_DISPLAYMODESELECTOR_H
#define __INC_LEDBOW_DISPLAYMODESELECTOR_H

#include <DisplayModeIsr.h>
#include <DisplayModeProcessor.h>

class DisplayModeSelector {
public:
  DisplayModeSelector() {
    modeIsr = DisplayModeIsr();
    processors = new DisplayModeProcessor*[processorCount];
    processorCount = 0;
  }

  void addProcessor(DisplayModeProcessor* processor) {
    DisplayModeProcessor** temp = new DisplayModeProcessor*[processorCount + 1];
    for (int i = 0; i < (processorCount); i++) {
      temp[i] = processors[i];
    }
    temp[processorCount] = processor;
    processorCount++;
    delete [] processors;
    processors = temp;
  }

  DisplayModeProcessor* selectProcessor() {
    int index = modeIsr.currentMode(processorCount);
    return processors[index];
  }

  void onInterrupt(unsigned long interruptTime) {
    modeIsr.onInterrupt(interruptTime);
  }

private:
  DisplayModeIsr modeIsr;
  DisplayModeProcessor** processors;
  int processorCount;
};

#endif
