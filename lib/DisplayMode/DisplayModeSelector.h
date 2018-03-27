#ifndef __INC_LEDBOW_DISPLAYMODESELECTOR_H
#define __INC_LEDBOW_DISPLAYMODESELECTOR_H

#include <DisplayMode.h>
#include <DisplayModeProcessor.h>
#include <Arduino.h>

class DisplayModeSelector {
public:
  DisplayModeSelector() {}

  void addProcessor(DisplayMode mode, DisplayModeProcessor* processor) {
    int index = static_cast<int>(mode);
    processors[index] = processor;
  }

  DisplayModeProcessor* selectProcessor(DisplayMode mode) {
    int index = static_cast<int>(mode);
    return processors[index];
  }

private:
  DisplayModeProcessor* processors[FINAL_DISPLAY_MODE_ENTRY];
};

#endif
