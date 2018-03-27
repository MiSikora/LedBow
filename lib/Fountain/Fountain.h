#ifndef __INC_LEDBOW_FOUNTAIN_H
#define __INC_LEDBOW_FOUNTAIN_H

#include <FastLED.h>

class Fountain {
public:
  const int length;

  Fountain(int length, CHSV firstColor, CHSV secondColor) : length(length), firstColor(firstColor), secondColor(secondColor) {
    background = new CHSV[length];
    for (int i = 0; i < length; i++) {
      background[i] = secondColor;
    }
    resetSeeds();
    resetBoundries();
  }

  void apply(CRGB leds[], int offset) {
    if (readyToReset) {
      return;
    }
    for (int i = offset; i < offset + length; i++) {
      leds[i] = background[i - offset];
    }
    if (newCycle) {
      newCycle = false;
      return;
    }
    leds[firstSeed + offset] = firstColor;
    leds[secondSeed + offset] = firstColor;
    firstSeed--;
    secondSeed++;
    if (firstSeed == leftBoundry && secondSeed == rightBoundry) {
      background[leftBoundry] = firstColor;
      background[rightBoundry] = firstColor;
      leftBoundry++;
      rightBoundry--;
      resetSeeds();
    }
    if (length % 2 == 0 && firstSeed == leftBoundry && secondSeed == rightBoundry) {
      background[leftBoundry] = firstColor;
      background[rightBoundry] = firstColor;
      readyToReset = true;
    } else if (length % 2 != 0 && firstSeed == rightBoundry && secondSeed == leftBoundry) {
      background[leftBoundry] = firstColor;
      background[rightBoundry] = firstColor;
      readyToReset = true;
    }
  }

  bool isReadyToReset() {
    return readyToReset;
  }

  void reset() {
    resetSeeds();
    resetBoundries();
    CHSV swapColor = firstColor;
    firstColor = secondColor;
    secondColor = swapColor;
  }

private:
  int firstSeed;
  int secondSeed;
  int leftBoundry;
  int rightBoundry;
  CHSV firstColor;
  CHSV secondColor;
  CHSV* background;
  bool readyToReset;
  bool newCycle;

  void resetSeeds() {
    if (length % 2 == 0) {
      secondSeed = length / 2;
      firstSeed = secondSeed - 1;
    } else {
      firstSeed = length / 2;
      secondSeed = firstSeed;
    }
    newCycle = true;
  }

  void resetBoundries() {
    leftBoundry = 0;
    rightBoundry = length - 1;
    readyToReset = false;
  }
};

#endif
