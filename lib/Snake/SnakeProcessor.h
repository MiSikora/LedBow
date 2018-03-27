#ifndef __INC_LEDBOW_SNAKECOLORPROCESSOR_H
#define __INC_LEDBOW_SNAKECOLORPROCESSOR_H

#include <DisplayModeProcessor.h>

class SnakeProcessor : public DisplayModeProcessor {
public:
  SnakeProcessor(int ledStripSize, CHSV* colors, int colorCount) : DisplayModeProcessor(ledStripSize), colorCount(colorCount) {
    this->colors = colors;
    snakeLength = 0;
    currentColor = 0;
  }

protected:
  void processLeds(CRGB leds[]) {
    CHSV color = colors[currentColor];
    CHSV snakeColor = colors[nextColor()];
    for (int i = 0; i < ledStripSize; i++) {
      leds[i] = color;
    }
    for (int i = 0; i < snakeLength; i++) {
      leds[i] = snakeColor;
    }
    snakeLength++;
    if (snakeLength == ledStripSize) {
      snakeLength = 0;
      currentColor = nextColor();
    }
  }

  unsigned long loopDelay() {
    return 60;
  }

private:
  const int colorCount;

  CHSV* colors;
  int snakeLength;
  int currentColor;

  int nextColor() {
    return (currentColor + 1) % colorCount;
  }
};

#endif
