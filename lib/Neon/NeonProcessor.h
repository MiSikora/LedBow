#ifndef __INC_LEDBOW_NEONPROCESSOR_H
#define __INC_LEDBOW_NEONPROCESSOR_H

#include <DisplayModeProcessor.h>

class NeonProcessor : public DisplayModeProcessor {
public:
  NeonProcessor(int ledStripSize, int cycleCount, unsigned long delay,
                uint8_t hue, uint8_t sat)
      : DisplayModeProcessor(ledStripSize), delay(delay) {
    neon = new CHSV[ledStripSize];
    int range = ledStripSize / cycleCount;
    int increment = 180 / range;
    int value = 0;
    for (int i = 0; i < ledStripSize; i++) {
      neon[i] = CHSV(hue, sat, value);
      value += increment;
      if (value > 255) {
        value -= 180;
      }
    }
    currentIndex = 0;
  }

protected:
  void processLeds(CRGB leds[]) {
    for (int i = 0, j = currentIndex; i < ledStripSize;
         i++, j = (j + 1) % ledStripSize) {
      leds[i] = neon[j];
    }
    currentIndex = (currentIndex + 1) % ledStripSize;
  }

  unsigned long loopDelay() { return delay; }

private:
  const unsigned long delay;

  CHSV *neon;
  int currentIndex;
};

#endif
