#ifndef __INC_LEDBOW_DISPLAYMODEPROCESSOR_H
#define __INC_LEDBOW_DISPLAYMODEPROCESSOR_H

#include <FastLED.h>

class DisplayModeProcessor {
public:
  DisplayModeProcessor(int ledStripSize) : ledStripSize(ledStripSize){};

  unsigned long applyProcessor(CRGB leds[]) {
    processLeds(leds);
    return loopDelay();
  }

protected:
  const int ledStripSize;

  virtual unsigned long loopDelay() { return 0; }

  virtual void processLeds(CRGB leds[]) = 0;
};

#endif
