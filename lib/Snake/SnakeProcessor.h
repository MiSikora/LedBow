#ifndef __INC_LEDBOW_SNAKEPROCESSOR_H
#define __INC_LEDBOW_SNAKEPROCESSOR_H

#include <DisplayModeProcessor.h>

class SnakeProcessor : public DisplayModeProcessor {
public:
  SnakeProcessor(int ledStripSize) : DisplayModeProcessor(ledStripSize) {
    snakeLength = 0;
    currentColor = 0;
    colorCount = 0;
    colors = new CHSV[colorCount];
  }

  void addColor(CHSV color) {
    CHSV* temp = new CHSV[colorCount + 1];
    for (int i = 0; i < colorCount; i++) {
      temp[i] = colors[i];
    }
    temp[colorCount] = color;
    colorCount++;
    delete [] colors;
    colors = temp;
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
  int colorCount;

  CHSV* colors;
  int snakeLength;
  int currentColor;

  int nextColor() {
    return (currentColor + 1) % colorCount;
  }
};

#endif
