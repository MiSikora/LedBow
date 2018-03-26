#include <DisplayModeIsr.h>
#include <DisplayModeSelector.h>
#include <SingleColorProcessor.h>

#define BUTTON_PIN 2

#define LED_PIN 6
#define NUM_LEDS 30

CRGB leds[NUM_LEDS];
DisplayModeIsr modeIsr = DisplayModeIsr();
DisplayModeSelector modeSelector = DisplayModeSelector();

void onInterrupt() {
  modeIsr.onInterrupt(millis());
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onInterrupt, RISING);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  modeSelector.addProcessor(NONE, new SingleColorProcessor(NUM_LEDS, CHSV(0, 0, 0)));
  modeSelector.addProcessor(RED, new SingleColorProcessor(NUM_LEDS, CHSV(0, 255, 255)));
  modeSelector.addProcessor(GREEN, new SingleColorProcessor(NUM_LEDS, CHSV(85, 255, 255)));
  modeSelector.addProcessor(BLUE, new SingleColorProcessor(NUM_LEDS, CHSV(170, 255, 255)));
}

void loop() {
  DisplayMode mode = modeIsr.currentMode();
  DisplayModeProcessor* processor = modeSelector.selectProcessor(mode);
  unsigned long sleepTime = processor->applyProcessor(leds);
  FastLED.show();
  delay(sleepTime);
}
