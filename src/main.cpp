#include <DisplayModeIsr.h>
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
DisplayModeIsr modeIsr = DisplayModeIsr();
DisplayModeSelector modeSelector = DisplayModeSelector();

void onInterrupt() {
  modeIsr.onInterrupt(millis());
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

  modeSelector.addProcessor(NONE, new SingleColorProcessor(NUM_LEDS, black));
  modeSelector.addProcessor(RED, new SingleColorProcessor(NUM_LEDS, red));
  modeSelector.addProcessor(GREEN, new SingleColorProcessor(NUM_LEDS, green));
  modeSelector.addProcessor(BLUE, new SingleColorProcessor(NUM_LEDS, blue));
  modeSelector.addProcessor(VIOLET, new SingleColorProcessor(NUM_LEDS, violet));
  modeSelector.addProcessor(YELLOW, new SingleColorProcessor(NUM_LEDS, yellow));
  modeSelector.addProcessor(CYAN, new SingleColorProcessor(NUM_LEDS, cyan));
  modeSelector.addProcessor(WHITE, new SingleColorProcessor(NUM_LEDS, white));
  modeSelector.addProcessor(RAINBOW, new RainbowProcessor(NUM_LEDS, 0, 255));
  modeSelector.addProcessor(FOUNTAIN, new FountainProcessor(NUM_LEDS, 2, green, violet));
  modeSelector.addProcessor(NEON, new NeonProcessor(NUM_LEDS, 2, blue.h, 120));
  modeSelector.addProcessor(SNAKE, new SnakeProcessor(NUM_LEDS, snakeColors, 6));
}

void loop() {
  DisplayMode mode = modeIsr.currentMode();
  DisplayModeProcessor* processor = modeSelector.selectProcessor(mode);
  unsigned long sleepTime = processor->applyProcessor(leds);
  FastLED.show();
  delay(sleepTime);
}
