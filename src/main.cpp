#include <DisplayModeSelector.h>
#include <SingleColorProcessor.h>
#include <RainbowProcessor.h>
#include <FountainProcessor.h>
#include <NeonProcessor.h>
#include <SnakeProcessor.h>

#define BUTTON_PIN 2

#define LED_PIN 6
#define NUM_LEDS 31

CRGB leds[NUM_LEDS];
DisplayModeSelector modeSelector = DisplayModeSelector();

void onInterrupt() {
  modeSelector.onInterrupt(millis());
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onInterrupt, RISING);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  CHSV black = CHSV(0, 0, 0);
  CHSV red = CHSV(0, 255, 255);
  CHSV green = CHSV(85, 255, 255);
  CHSV blue = CHSV(170, 255, 255);
  CHSV violet = CHSV(191, 255, 255);
  CHSV yellow = CHSV(43, 255, 255);
  CHSV cyan = CHSV(128, 255, 255);
  CHSV white = CHSV(0, 0, 255);
  CHSV snakeColors[] = { red, yellow, green, cyan, blue, violet };

  modeSelector.addProcessor(new SingleColorProcessor(NUM_LEDS, black));
  modeSelector.addProcessor(new SingleColorProcessor(NUM_LEDS, red));
  modeSelector.addProcessor(new SingleColorProcessor(NUM_LEDS, green));
  modeSelector.addProcessor(new SingleColorProcessor(NUM_LEDS, blue));
  modeSelector.addProcessor(new SingleColorProcessor(NUM_LEDS, violet));
  modeSelector.addProcessor(new SingleColorProcessor(NUM_LEDS, yellow));
  modeSelector.addProcessor(new SingleColorProcessor(NUM_LEDS, cyan));
  modeSelector.addProcessor(new SingleColorProcessor(NUM_LEDS, white));
  modeSelector.addProcessor(new RainbowProcessor(NUM_LEDS, 0, 255));
  modeSelector.addProcessor(new FountainProcessor(NUM_LEDS, 2, green, violet));
  modeSelector.addProcessor(new NeonProcessor(NUM_LEDS, 2, blue.h, 120));
  modeSelector.addProcessor(new SnakeProcessor(NUM_LEDS, snakeColors, 6));
}

void loop() {
  DisplayModeProcessor* processor = modeSelector.selectProcessor();
  unsigned long sleepTime = processor->applyProcessor(leds);
  FastLED.show();
  delay(sleepTime);
}
