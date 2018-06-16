#ifndef __INC_LEDBOW_STROBOSCOPEPROCESSOR_H
#define __INC_LEDBOW_STROBOSCOPEPROCESSOR_H

#include <DisplayModeProcessor.h>

class StroboscopeProcessor : public DisplayModeProcessor {
public:
  StroboscopeProcessor(int ledStripSize) : DisplayModeProcessor(ledStripSize) {
    blackout = false;
    colorCount = 0;
    colors = new CHSV[colorCount];
    currentColor = 0;
  }

  void addColor(CHSV color) {
    CHSV *temp = new CHSV[colorCount + 1];
    for (int i = 0; i < colorCount; i++) {
      temp[i] = colors[i];
    }
    temp[colorCount] = color;
    colorCount++;
    delete[] colors;
    colors = temp;
  }

protected:
  void processLeds(CRGB leds[]) {
    CHSV color;
    if (blackout) {
      color = black;
    } else {
      color = colors[nextColor()];
    }
    for (int i = 0; i < ledStripSize; i++) {
      leds[i] = color;
    }
    blackout = !blackout;
  }

  unsigned long loopDelay() { return 80; }

private:
  const CHSV black = CHSV(0, 0, 0);
  bool blackout;
  int colorCount;
  CHSV *colors;
  int currentColor;

  int nextColor() {
    currentColor = (currentColor + 1) % colorCount;
    return currentColor; 
  }
};

#endif
