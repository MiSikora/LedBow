#ifndef __INC_LEDBOW_RAINBOWPROCESSOR_H
#define __INC_LEDBOW_RAINBOWPROCESSOR_H

#include <DisplayModeProcessor.h>

class RainbowProcessor : public DisplayModeProcessor {
public:
  RainbowProcessor(int ledStripSize, uint8_t start, uint8_t end)
      : DisplayModeProcessor(ledStripSize) {
    rainbow = new CHSV[ledStripSize];
    int range = 0;
    if (end > start) {
      range = end - start;
    } else {
      range = 255 - start + end;
    }
    int increment = (uint8_t)((float)range / (float)ledStripSize);
    int hue = start;
    for (int i = 0; i < ledStripSize; i++) {
      rainbow[i] = CHSV(hue, 255, 255);
      hue += increment;
      if (hue > 255) {
        hue -= 255;
      }
    }
    currentIndex = 0;
  }

protected:
  void processLeds(CRGB leds[]) {
    for (int i = 0, j = currentIndex; i < ledStripSize;
         i++, j = (j + 1) % ledStripSize) {
      leds[i] = rainbow[j];
    }
    currentIndex = (currentIndex + 1) % ledStripSize;
  }

  unsigned long loopDelay() { return 40; }

private:
  CHSV *rainbow;
  int currentIndex;
};

#endif
