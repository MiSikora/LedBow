#include <DisplayModeIsr.h>
#include <SingleColorProcessor.h>

#define BUTTON_PIN 2

#define LED_PIN 6
#define NUM_LEDS 30

DisplayModeIsr modeIsr = DisplayModeIsr();
SingleColorProcessor blackProcessor = SingleColorProcessor(NUM_LEDS, CHSV(0, 0, 0));
SingleColorProcessor redProcessor = SingleColorProcessor(NUM_LEDS, CHSV(0, 255, 255));
SingleColorProcessor greenProcessor = SingleColorProcessor(NUM_LEDS, CHSV(85, 255, 255));
SingleColorProcessor blueProcessor = SingleColorProcessor(NUM_LEDS, CHSV(170, 255, 255));

CRGB leds[NUM_LEDS];

void onInterrupt() {
  modeIsr.onInterrupt();
}

void setup() {
  Serial.begin(57600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onInterrupt, RISING);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  unsigned long sleepTime = 0;
  switch (modeIsr.currentMode()) {
    case NONE:
    sleepTime = blackProcessor.applyProcessor(leds);
    break;

    case RED:
    sleepTime = redProcessor.applyProcessor(leds);
    break;

    case GREEN:
    sleepTime = greenProcessor.applyProcessor(leds);
    break;

    case BLUE:
    sleepTime = blueProcessor.applyProcessor(leds);
    break;
  }
  FastLED.show();
  delay(sleepTime);
}
