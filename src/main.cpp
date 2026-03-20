#include <Arduino.h>
#include <fastLED.h>

#define NUM_RINGS 5
#define LEDS_PER_RING 45

#define DATA_PIN    6
#define NUM_LEDS    NUM_RINGS * LEDS_PER_RING   // Total number of LEDs
#define LED_TYPE    WS2812B                     // LED Type
#define COLOR_ORDER GRB                         // Color channel order

CRGB leds[NUM_LEDS];

void setup() {
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(50);
}

void loop() {
  static uint8_t hue = 0;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(hue + (uint8_t) i, 255, 255);
    }
    FastLED.show();
    delay(10);
    hue++;
}
