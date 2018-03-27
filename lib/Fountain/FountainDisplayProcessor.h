#ifndef __INC_LEDBOW_FOUNTAINCOLORPROCESSOR_H
#define __INC_LEDBOW_FOUNTAINCOLORPROCESSOR_H

#include <DisplayModeProcessor.h>
#include <Fountain.h>

class FountainDisplayProcessor : public DisplayModeProcessor {
public:
  FountainDisplayProcessor(int ledStripSize, int fountainCount, CHSV firstColor, CHSV secondColor) : DisplayModeProcessor(ledStripSize), fountainCount(fountainCount) {
    fountains = new Fountain*[fountainCount];
    int length = ledStripSize / fountainCount;
    int lengthRemainder = ledStripSize % fountainCount;
    for (int i = 0; i < fountainCount; i++) {
      int fountainLength = length;
      if (lengthRemainder > 0) {
        lengthRemainder--;
        fountainLength++;
      }
      fountains[i] = new Fountain(fountainLength, firstColor, secondColor);
    }
  }

protected:
  void processLeds(CRGB leds[]) {
    int offset = 0;
    bool reset = true;
    for (int i = 0; i < fountainCount; i++) {
      if (i > 0) {
        offset += fountains[i - 1]->length;
      }
      fountains[i]->apply(leds, offset);
      reset = reset && fountains[i]->isReadyToReset();
    }
    if (reset) {
      for (int i = 0; i < fountainCount; i++) {
        fountains[i]->reset();
      }
    }
  }

  unsigned long loopDelay() {
    return 40;
  }

private:
  const int fountainCount;

  Fountain** fountains;
};

#endif
