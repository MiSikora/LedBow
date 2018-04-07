#ifndef __INC_LEDBOW_SINGLECOLORPROCESSOR_H
#define __INC_LEDBOW_SINGLECOLORPROCESSOR_H

#include <DisplayModeProcessor.h>

class SingleColorProcessor : public DisplayModeProcessor {
public:
  SingleColorProcessor(int ledStripSize, CHSV color)
      : DisplayModeProcessor(ledStripSize), color(color) {}

protected:
  void processLeds(CRGB leds[]) {
    for (int i = 0; i < ledStripSize; i++) {
      leds[i] = color;
    }
  }

private:
  const CHSV color;
};

#endif
